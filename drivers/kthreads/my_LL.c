#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>
#include<linux/spinlock.h>
#include <linux/kthread.h>

static struct task_struct *mythread = NULL;
static spinlock_t my_lock;
struct da 
{
    int No_of_packets;
};

struct Queue
{
    struct list_head list;  // linked list
    struct da *data_urb;   // queue data
};
struct Queue head1,*newNode1;


void Enqueue(struct Queue *hptr, struct da *urb)
{
    unsigned long Eq_flag;
    struct Queue *qdata;
INIT_LIST_HEAD(&head1.list); // list head initialized 
    qdata = (struct Queue *) kzalloc(sizeof(struct Queue),GFP_ATOMIC);

    if(!qdata)
    {
        printk(KERN_ALERT "Enqueue:kzalloc failed\n");
    }

    qdata->data_urb = urb;
    spin_lock_irqsave(&my_lock, Eq_flag);
    list_add_tail(&(qdata->list),&(hptr->list));
    spin_unlock_irqrestore(&my_lock,Eq_flag);
    printk("\n%s: called from this LINE:%d\n", __func__,__LINE__);
}

int threadfn_Dequeue(void *d)
{

            unsigned long int Dq_flag;
    printk("\n%s: called from this LINE:%d\n", __func__,__LINE__);

    while (!kthread_should_stop()) {/*The thread cannot exit until the 
                                     *kthread_should_stop() function returns 1*/
        while(!list_empty(&head1.list)){
            struct Queue *qdata1;
            printk("\n%s:while 1 called from this LINE:%d\n", __func__,__LINE__);
            spin_lock_irqsave(&my_lock, Dq_flag);
            qdata1 = list_first_entry((head1.list.next),struct Queue,list);
            spin_unlock_irqrestore(&my_lock,Dq_flag);

            printk("\n%s: called from this LINE:%d\n", __func__,__LINE__);
                printk("\n%s: called from this LINE:%d:npkt:=%d\n", __func__,__LINE__,qdata1->data_urb->No_of_packets);
            list_del(&(qdata1->list));
            kfree(qdata1);
        }
        printk("empty\n");
    }

return 0;
}


// Module Initialization
 static int __init init_thread(void)
 {

    int i;
    struct da *urb;

 //  urb = (struct Queue *) kzalloc(sizeof(struct Queue),GFP_ATOMIC);
   urb = kzalloc(sizeof(struct da),GFP_ATOMIC);
    for(i=1;i<=5;i++)
    {
        urb->No_of_packets = i*5;
        Enqueue(&head1,urb);
    }
    mythread = kthread_run(threadfn_Dequeue,NULL,"kernel_thread");
    if (mythread)
        printk(KERN_INFO "Thread Created successfully\n");
    else
        printk(KERN_ERR "Thread creation failed\n");
    return 0;
}
// Module Exit
static void __exit cleanup_thread(void)
{
    if (mythread)
    {
        kthread_stop(mythread);
        printk(KERN_INFO "Thread stopped");
    }





}


module_init(init_thread);
module_exit(cleanup_thread);
MODULE_LICENSE("GPL");

