#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/version.h>


MODULE_LICENSE("GPL");
extern int ofcd();
static int ofcd_init(void)
{
printk(KERN_INFO "hello world");
ofcd();
return 0;

}
static void ofcd_exit(void)
{

printk(KERN_INFO "goodbye world");

}

module_init(ofcd_init);
module_exit(ofcd_exit);
