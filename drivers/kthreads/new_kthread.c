#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/udp.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/kthread.h>

struct task_struct *task1;
struct task_struct *task2;


static void thread_func(void* data)
{   
	int *n;
	n = (int *)data;
	int i = 0;
	while(i < 10){
		printk("%d\n", *n);
		schedule();
		i++;
		if(kthread_stop())
			break;
	}
	return 0;
}

static int t_start(void)
{
	printk("Module starting ... ... ..\n");
	int *p1, *p2;
	int one = 1, two = 2;
	p1 = &one;
	p2 = &two;
	task1 = kthread_run(thread_func, (void*)p1, "thread_func_1");
	task2 = kthread_run(thread_func, (void*)p2, "thread_func_2");
	return 0;
}

static void t_end (void)
{
	printk("Module terminating ... ... ...\n");
	kthread_stop(task1);
	kthread_stop(task2);
}

module_init(t_start);
module_exit(t_end);

MODULE_AUTHOR("CMNKR");
MODULE_DESCRIPTION("Testing kernel threads");
MODULE_LICENSE("GPL");


