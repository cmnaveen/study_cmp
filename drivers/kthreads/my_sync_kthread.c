#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

struct kthr_data {
	const char *name;
	wait_queue_head_t thrdwq; // kernel thread waits on this queue 
				//wait_queue_head_t is the list head other nodes are wait_queue_t 
				//nodes which holds the task (function pointer)
	int condition;
	struct kthr_data *datalink;
};

static struct kthr_data done, dzero;


int kthread_function1(void* data1)
{
	struct kthr_data *pdata1 = (struct kthr_data*)data1; // this data depends on the kernel thread running "one"/"zero"
	while(1)
	{
		printk("wait(%s)", pdata1->name);
		wait_event_interruptible(pdata1->thrdwq, pdata1->condition);
		pdata1->condition = 0;
		printk("%s\n",pdata1->name);
	//	mdelay(500);
	//	msleep(1);
//			schedule();
		pdata1->datalink->condition = 1;
		printk("wakeup (%s)\n", pdata1->name);
		wake_up_interruptible(&pdata1->datalink->thrdwq);//wake up the //task waiting in queue
		if(kthread_should_stop())
			break;
	}
	return 0;

}
int kthread_function2(void* data2)
{
	struct kthr_data *pdata2 = (struct kthr_data*)data2; // this data depends on the kernel thread running "one"/"zero"
	while(1)
	{
		printk("wait(%s)", pdata2->name);
		wait_event_interruptible(pdata2->thrdwq, pdata2->condition);
		pdata2->condition = 0;
		printk("%s\n",pdata2->name);
	//	mdelay(500);
	//	msleep(1);
//			schedule();
		pdata2->datalink->condition = 1;
		printk("wakeup (%s)\n", pdata2->name);
		wake_up_interruptible(&pdata2->datalink->thrdwq);//wake up the //task waiting in queue
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

	tone = kthread_run(kthread_function1, &done, "one");
	tzero = kthread_run(kthread_function2, &dzero, "zero");
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
