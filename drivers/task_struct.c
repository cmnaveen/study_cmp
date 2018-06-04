#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>


MODULE_LICENSE("GPL");

static int test_init(void)
{

struct task_struct *task;
for_each_process(task)
{

printk("process Name:%s\t PID:%d\t process state:%ld\n",task->comm,task->pid,task->state);
}
return 0;
}

static void test_exit(void){
printk(KERN_INFO "cleaning up\n");

}
module_init(test_init);
module_exit(test_exit);
