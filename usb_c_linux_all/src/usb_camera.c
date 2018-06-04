#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/slab.h>
#include <linux/debugfs.h>
#include <media/v4l2-common.h>
#include <media/v4l2-device.h>
#include <linux/videodev2.h>
#include <media/v4l2-ctrls.h>

#define npackets 6
#define NUM_URBS 5

struct usb_class_driver class;
struct dentry *debug_file;
struct dentry *debug_dir;
struct file *fp;
int glob = 1;
loff_t pos = 0 ;
mm_segment_t oldfs ;
//int pos = 0;

//char filename[] = "samplefile.yuv";
//FILE *fp;

MODULE_LICENSE ("Dual BSD/GPL");
MODULE_AUTHOR("CM Naveen Reddy");                                                  
MODULE_DESCRIPTION("USB Registration Driver");                                  

static struct usb_device_id usb_idtable[] =
{
	{ USB_DEVICE (0x046d, 0x0837)},
//046d:0837
	//	.driver_info {}
	{}
};
MODULE_DEVICE_TABLE (usb, usb_idtable);

struct usb_camera_device {
	struct usb_device *udev;                                                    
	struct usb_interface *intf;                                                 
	int intfnum;                                                                
	char name[32];

	struct mutex lock;
	struct v4l2_device vdev;

	struct usb_host_endpoint *ep;                                           
	struct urb *urb[5];
	int urb_size;
	__u8 *status;
}*dev;

void streamon (void)
{
	int i = 0;

	for (i = 0; i < NUM_URBS; i++) {
		if (usb_submit_urb (dev->urb[i], GFP_KERNEL) != 0) 
			printk (KERN_ERR "Failed to submit URB\n");
	}
}

void streamoff (void)
{
	int i = 0;

	for (i = 0; i < NUM_URBS; i++) {
		if (usb_unlink_urb (dev->urb[i]) != -EINPROGRESS) 
			printk (KERN_ERR "Failed to unlink URB\n");
	}

	filp_close (fp,NULL);
}

static void copy_video_data_to_file (void *ptr, int size)
{
	//	fwrite (ptr, size, 1, fp);
	int len = 0;

	printk ("%s\n\n", (char *)ptr);

	fp->f_pos = pos;                                                      
	if (size) {                          
		len = vfs_write (fp, ptr, size,&fp->f_pos);                                              
		if (len < 0) {                                                          
			printk (KERN_ERR "vfs_write failed\n");                                      
		}                                                                       
	}                                                                           
	pos = pos + len; 

	//	vfs_write (f ,ptr ,size ,&pos);
}

static void urb_status_complete (struct urb *urb)                                
{                                                                               
	struct usb_camera_device *dev = urb->context;                                      
	int ret;                                                               

	switch (urb->status) {                                                      
		case 0:                                                                     
			break;                                                                  

		case -ENOENT:       /* usb_kill_urb() called. */                            
		case -ECONNRESET:   /* usb_unlink_urb() called. */                          
		case -ESHUTDOWN:    /* The endpoint is being disabled. */                   
		case -EPROTO:       /* Device is disconnected (reported by some             
							 * host controller). */                                         
			return;                                                                 

		default:                                                                    
			printk (KERN_WARNING "Non-zero status (%d)\n", urb->status);                              
			return;                                                                 
	}                                                                           

	copy_video_data_to_file (urb->transfer_buffer, urb->actual_length);

	/* Resubmit the URB. */                                                     
	urb->interval = dev->ep->desc.bInterval;

	if ((ret = usb_submit_urb (urb, GFP_KERNEL)) < 0)
		printk(KERN_ERR "Failed to resubmit status URB (%d).\n",ret);                
}

static unsigned int camera_endpoint_max_bpi(struct usb_device *dev,                
		struct usb_host_endpoint *ep)                              
{                                                                               
	__u16 psize;                                                                  
	__u16 mult;                                                                   

	if (dev && ep) {
		//		printk("Address here %x %x",dev,ep);
		switch (dev->speed) {                                                       
			case USB_SPEED_SUPER:                                                       
//			case USB_SPEED_SUPER_PLUS:                                                  
				return le16_to_cpu(ep->ss_ep_comp.wBytesPerInterval);                   
			case USB_SPEED_HIGH:                                                        
				psize = usb_endpoint_maxp(&ep->desc);                                   
				//mult = usb_endpoint_maxp_mult(&ep->desc);                               
				return (psize & 0x07ff) * mult;                                         
			case USB_SPEED_WIRELESS:                                                    
				psize = usb_endpoint_maxp(&ep->desc);                                   
				return psize;                                                           
			default:                                                                    
				psize = usb_endpoint_maxp(&ep->desc);                                   
				return psize & 0x07ff;                                                  
		}           	
	} else {
		//		printk("NULL here %x %x",dev,ep);
	}

	return 0;
}

/*
 * static int uvc_init_video_isoc(struct uvc_streaming *stream,                    
 * struct usb_host_endpoint *ep, gfp_t gfp_flags)                              
 */
static int urb_init (struct usb_camera_device *dev)                                     
{                                                                               
	struct usb_host_endpoint *ep = dev->ep;                                 
	unsigned int i, j;                                                
	int pipe;
	int interval;
	u16 psize; 
	u32 size;                                                                   

	psize = camera_endpoint_max_bpi (dev->udev, dev->intf->cur_altsetting->endpoint);                        

	printk (KERN_INFO "packet size %d\n", psize);

	size = npackets * psize;                                                    

	pipe = usb_rcvisocpipe (dev->udev, ep->desc.bEndpointAddress);                

	interval = ep->desc.bInterval;                                              
	if ((interval > 16) && (dev->udev->speed == USB_SPEED_HIGH))                              
		interval = fls(interval) - 1;                                           

	for (i = 0; i < NUM_URBS; ++i) {                                            
		dev->urb[i] = usb_alloc_urb (npackets, GFP_KERNEL);                               
		if (dev->urb[i] == NULL) {                                                      
			return -ENOMEM;                                                     
		}                                                                       

		dev->urb[i]->dev = dev->udev;
		dev->urb[i]->context = dev;
		dev->urb[i]->pipe = pipe;
		dev->urb[i]->interval = interval;
		dev->urb[i]->transfer_flags = URB_ISO_ASAP;
		dev->urb[i]->transfer_buffer = kmalloc (size, GFP_KERNEL);                           

		if (!dev->urb[i]->transfer_buffer) 
			printk(KERN_ERR "Failed to allocate memory");                

		dev->urb[i]->complete = urb_status_complete;
		dev->urb[i]->number_of_packets = npackets;
		dev->urb[i]->transfer_buffer_length = size;

		for (j = 0; j < npackets; j++) {
			dev->urb[i]->iso_frame_desc[j].offset = j * psize;
			dev->urb[i]->iso_frame_desc[j].length = psize;
		}
	}

	return 0;                                                                   
}                                                                               

int parse_interface(struct usb_camera_device *dev)
{
	struct usb_host_interface *alts = dev->intf->cur_altsetting;                

	if (alts->desc.bNumEndpoints == 1) {                            
		struct usb_host_endpoint *ep = &alts->endpoint[0];                      
		struct usb_endpoint_descriptor *desc = &ep->desc;                       

		//		printk ("endianess %x %x",le16_to_cpu(desc->wMaxPacketSize),desc->wMaxPacketSize);

		if (le16_to_cpu(desc->wMaxPacketSize) >= 8 && desc->bInterval != 0) {                                             
			printk (KERN_INFO "Found a valid endpoint\n(addr %02x).\n", desc->bEndpointAddress);                      
			dev->ep = ep;                                                   
		}                                                                       

		if ((ep->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) 
				== USB_ENDPOINT_XFER_ISOC){
			printk("endpoint is ISOC");
		}
	}

	return 0;
}

int device_open(struct inode *inode, struct file *filep)
{
	printk(KERN_INFO "Open successful\n");

	return 0;
}

long stream_ioctl(struct file *fp, unsigned int pid, unsigned long num )
{
	struct module *my_module = THIS_MODULE;
	//	struct task_struct *my_task = current;

	printk(KERN_INFO "module name %s\n", my_module->name);

	if (num == 1) 
		streamon ();
	else if (num == 0) 
		streamoff ();

	return 0;
}

const struct file_operations fops = {                            
	.owner = THIS_MODULE,
	.open = device_open,
	.unlocked_ioctl = stream_ioctl
};

static int usb_probe(struct usb_interface *interface, 
		const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);                        

	if (interface->cur_altsetting->desc.bInterfaceNumber != 1) 
		return -1;

	class.name = "usb/camera%d";                                           
	class.fops = &fops;                                             

	if (usb_register_dev(interface, &class) != 0) {
		printk (KERN_ERR "uable to register in dev\n");
		goto err_class_create;
	}

	if (id->idVendor && id->idProduct )
		printk (KERN_INFO "Probing known USB device %s " "(%04x:%04x)\n", 
				udev->devpath, id->idVendor,id->idProduct);                     
	else
		printk (KERN_INFO "Probing generic USB device %s\n", udev->devpath);

	if (0 != (usb_set_interface (udev, 1, 4) )) {
		printk (KERN_INFO "can't set 1,4 interface\n");
		return -1;
	}

	printk("current alt_setting %d num of altsets %d", 
			interface->cur_altsetting->desc.bAlternateSetting,interface->num_altsetting);

	if ( interface->cur_altsetting->string)
		printk("string %s", interface->cur_altsetting->string);
	else 
		printk("NULL string");

	/* Allocate memory for the device and initialize it. */                     
	if ((dev = (struct usb_camera_device *) kzalloc 
				(sizeof(struct usb_camera_device), GFP_KERNEL)) == NULL)                       
		goto err_clear_struct;

	//mutex_init (&dev->lock);                                                     

	dev->udev = usb_get_dev(udev);                                              
	dev->intf = usb_get_intf(interface);                                             
	dev->intfnum = interface->cur_altsetting->desc.bInterfaceNumber;

	if (udev->product != NULL)                                                  
		strlcpy (dev->name, udev->product, strlen( udev->product));  
	else                                                                        
		snprintf (dev->name, strlen (dev->name), "USB_Camera (%04x:%04x)", 
				le16_to_cpu(udev->descriptor.idVendor),                             
				le16_to_cpu(udev->descriptor.idProduct));

	parse_interface(dev);

	//	if (v4l2_device_register(&interface->dev, &dev->vdev) < 0)
	//		goto error;
	//	usb_set_intfdata (interface, dev);

	urb_init (dev);

	fp = filp_open("/home/naveen/sample.yuv", O_RDWR |  O_LARGEFILE, 0);                                        
	if (fp)                                                           
		printk (KERN_INFO "file opened with fd = %p\n", fp);                   
	else                                                                    
		printk ("File opened failed\n"); 
/*
	f = filp_open ("/tmp/data1" , O_RDWR, 0) ;
	if ( IS_ERR(f) || f == NULL ) {
		printk ("file opening failed\n") ;
		goto err_close_file;
	}
*/
	return 0;

err_close_file:
	filp_close (fp,NULL);

err_clear_struct:
	kfree (dev);

err_class_create:
	usb_deregister_dev (dev->intf, &class);

	return -1;
}

static void usb_disconnect(struct usb_interface *interface)                       
{
	streamoff ();

	usb_deregister_dev (dev->intf, &class);
	printk (KERN_INFO "logi camera removed\n");
} 

static struct usb_driver usb_camera =
{
	.name = "usb_camera",
	.id_table = usb_idtable,
	.probe = usb_probe,
	.disconnect = usb_disconnect,
};

static int __init usb_init (void)
{

	return usb_register (&usb_camera);
}

static void __exit usb_exit (void)
{

	usb_deregister (&usb_camera);
}

module_init (usb_init);
module_exit (usb_exit);
