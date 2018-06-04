#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>

static int __init ofd_init(void)
{



printk( KERN_INFO "ofcd: registered");
return 0;

}
static ofcd(void) {
printk(KERN_INFO "Hello from another module");
return 0;
} 

static void __exit ofd_exit(void)
{

printk( KERN_INFO "ofcd: unregistered");

}
EXPORT_SYMBOL(ofcd);
module_init(ofd_init);
module_exit(ofd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("naveen");


