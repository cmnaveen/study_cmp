#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

extern hello_ex;

static int hel_init(void)
{
printk(KERN_INFO "hello world");
return 0;
}


static void hel_exit(void)
{
printk(KERN_INFO "goodbye world");

}

MODULE_LICENSE("Dual BSD/GPL");
module_init(hel_init);
module_exit(hel_exit);
