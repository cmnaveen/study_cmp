#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>



static int hello_init(void)
{
printk(KERN_INFO "hello world");
return 0;
}

static hello_ex(void)
{
printk(KERN_INFO "hello from another module");
return 0;
}

static void hello_exit(void)
{
printk(KERN_INFO "goodbye world");

}

EXPORT_SYMBOL(hello_ex);
MODULE_LICENSE("Dual BSD/GPL");
module_init(hello_init);
module_exit(hello_exit);
