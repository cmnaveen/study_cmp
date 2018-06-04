#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
MODULE_LICENSE("GPL");
//int paramTest;
int paramArray[3];
module_param_array(paramArray, int,NULL,S_IRUSR|S_IWUSR);
static int param_init(void){
	printk(KERN_ALERT "Showing the parameter demo");
	printk(KERN_ALERT "VALUE OF PARAMTEST IS: %d \t %d\t%d",paramArray[0],paramArray[2],paramArray[1]);
	return 0;
}
static void param_exit(void){
	printk(KERN_ALERT "Exiting the parameter demo");
}
module_init(param_init);
module_exit(param_exit);
