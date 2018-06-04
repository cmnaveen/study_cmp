#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/jiffies.h>

  static int __init ofcd_init(void);
static void __exit ofcd_exit(void); /* Destructor */
static dev_t first; // Global variable for the first device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class
static int my_open(struct inode *i, struct file *f)
{
printk(KERN_ALERT "\n--->DEBUG: Passed %s %d \n",__FUNCTION__,__LINE__); 
printk("\n--->%s:%d - %s\n", __FILE__, __LINE__, __func__ );  

	printk(KERN_INFO "Driver: open()\n");
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
printk("\n--->%s:%d - %s\n", __FILE__, __LINE__, __func__ );  

	printk(KERN_INFO "Driver: close()\n");
	return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t
		len, loff_t *off)
{
printk("\n--->%s:%d - %s\n", __FILE__, __LINE__, __func__ );  
	printk(KERN_INFO "Driver: read()\n");
	return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf,
		size_t len, loff_t *off)
{
printk("\n--->%s:%d - %s\n", __FILE__, __LINE__, __func__ );  
	printk(KERN_INFO "Driver: write()\n");
	return len;
}
static struct file_operations pugs_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};

 /* Constructor */

/*
 * static int __init ofcd_init(void){
printk("\n--->%s:%d - %s\n", __FILE__, __LINE__, __func__ );  

	printk(KERN_INFO "Namaskar: ofcd registered:-");
	if (alloc_chrdev_region(&first, 0, 1, "Shweta") < 0)
	{
		return -1;
	}
	if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		unregister_chrdev_region(first, 1);
		return -1;
	}
	if (device_create(cl, NULL, first, NULL, "mynull") == NULL)
	{
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	cdev_init(&c_dev, &pugs_fops);
	if (cdev_add(&c_dev, first, 1) == -1)
	{
		device_destroy(cl, first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	return 0;
}
*/
//static void __exit ofcd_exit(void) /* Destructor */
/*{
	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "nvr: ofcd unregistered");
printk("%s:%d - %s", __FILE__, __LINE__, __func__ );  
}
*/
module_init(ofcd_init);
module_exit(ofcd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("naveen venkat ravi");
MODULE_DESCRIPTION("Our First Character Driver");