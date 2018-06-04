#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>
void myfunc(void)
{
    char *ptr;
    ptr = vmalloc(512);
}
static int my_init(void)
{
    printk(KERN_ALERT "Hello World");
    myfunc();
    return 0;
}
static void my_exit(void)
{
    printk(KERN_ALERT "Exit");
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sample_module");
