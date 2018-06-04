#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

struct kthr_data {
	const char *name;
	//wq<--wqh-->wq
	wait_queue_head_t thrdwq; // kernel thread waits on this queue 
				//wait_queue_head_t is the list head other nodes are wait_queue_t 
				//nodes which holds the task (function pointer)
	int condition;
	struct kthr_data *datalink;
};

static struct kthr_data done, dzero;


int kthread_function(void* data)
{
	struct kthr_data *pdata = (struct kthr_data*)data; // this data depends on the kernel thread running "one"/"zero"
	while(1)
	{
		printk("wait(%s)", pdata->name);
		wait_event_interruptible(pdata->thrdwq, pdata->condition);
		pdata->condition = 0;
		printk("%s\n",pdata->name);
		mdelay(500);
		msleep(1);
		pdata->datalink->condition = 1;
		printk("wakeup (%s)\n", pdata->name);
		wake_up_interruptible(&pdata->datalink->thrdwq);//wake up the //task waiting in queue
		if(kthread_should_stop())
			break;
	}
	return 0;

}



struct task_struct *tone, *tzero;

int __init kthread_init(void)
{
	printk("\nkthread init");
	init_waitqueue_head(&done.thrdwq);
	init_waitqueue_head(&dzero.thrdwq);
	done.condition = 1;
	dzero.condition = 0;
	done.name = "one";
	dzero.name = "zero";
	done.datalink = &dzero;
	dzero.datalink = &done;

	tone = kthread_run(kthread_function, &done, "one");
	tzero = kthread_run(kthread_function, &dzero, "zero");
	return 0;
}

void __exit kthread_exit(void)
{
	printk("\nkernel exit thread");
	kthread_stop(tone);
	kthread_stop(tzero);
}

module_init(kthread_init);

module_exit(kthread_exit);
