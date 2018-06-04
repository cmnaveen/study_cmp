#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>
static dev_t first; //globle variable for the device no
int __init ofd_init(void) /*const*/
{
	printk(KERN_INFO "NAMSAKAR:ofd reg");
	if(alloc_chrdev_region(&first, 0, 3, "CMNKR") <0)
	{
		return-1;
	}
	printk(KERN_INFO "<Major,Minor>: <%d ,%d> \n",MAJOR(first),MINOR(first));
	return 0;
}
static void __exit ofd_exit(void)/*Destructor*/
{
	unregister_chrdev_region(first, 3);
	printk(KERN_INFO "by Gn:ofd unreg");
}
module_init(ofd_init);
module_exit(ofd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CM");
MODULE_DESCRIPTION("OUR FIRST character DRIVER");
