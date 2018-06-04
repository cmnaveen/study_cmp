#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/syscalls.h> 
#include <linux/file.h> 
#include <linux/fs.h>
#include <linux/fcntl.h> 
#include <asm/uaccess.h> 

static struct urb *urb;
static void write_file(char *filename,char *urb_buffer[UVC_URBS])
{
		struct file *file;
		loff_t pos = 0;
		int fd;

		mm_segment_t old_fs = get_fs();
		set_fs(KERNEL_DS);

		fd = sys_open(filename, O_WRONLY|O_CREAT, 0644);

		if (fd >= 0) {
				sys_write(fd,urb_buffer[UVC_URBS],strlen(urb_buffer[UVC_URBS]));
				file = fget(fd);
				if (file) {
						vfs_write(file, *urb_buffer[UVC_URBS], strlen(urb_buffer[UVC_URBS] ), &pos);
						fput(file);

				}
				sys_close(fd);

		}
		set_fs(old_fs);

}

static int __init init(void)
{
		write_file("/dev/video0", urb);
		return 0;

}

static void __exit exit(void)
{  }

MODULE_LICENSE("GPL");
module_init(init);
module_exit(exit);

