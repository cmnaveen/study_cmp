#include <linux/slab.h>
#ifndef QUEUE_H_
#define QUEUE_H_

#include <linux/list.h>
#include <linux/spinlock.h>

typedef struct QueueItem
{
   struct list_head    list;      // Linked List
   void *              item;      // Item of Data
} QueueItem;

typedef struct Queue
{
   struct list_head    list;      // List Head
   spinlock_t          lock;      // Lock
} Queue;

// Prototypes

Queue *  qCreate(void);
void     qDelete(Queue *q);
void     qEnqueue(Queue *q, void *item);
void *   qDequeue(Queue *q);
int      qIsEmpty(Queue *q);
int      qLock(Queue *q);
void     qUnlock(Queue *q);

#endif   // QUEUE_H_


Queue * qCreate(void)
{
	Queue *    q;

	q = (Queue *) kmalloc(sizeof(Queue), GFP_ATOMIC);
	if (! q)
	{
		printk(KERN_ALERT "qCreate:kmalloc failed\n");
		return q;
	}

	INIT_LIST_HEAD(&(q->list));

	spin_lock_init(&(q->lock));

	return q;
}

// Queue must be empty!
void qDelete(Queue *q)
{

	kfree((void *) q);

	return;
}

void qEnqueue(Queue *q, void *item)
{
	QueueItem *   qi;

	qi = (QueueItem *) kmalloc(sizeof(QueueItem), GFP_ATOMIC);
	if (! qi)
	{
		printk(KERN_ALERT "qEnqueue:kmalloc failed\n");
		return;
	}

	qi->item = item;

	spin_lock(&(q->lock));
	list_add_tail(&(qi->list), &(q->list));
	spin_unlock(&(q->lock));

	return;
}

void * qDequeue(Queue *q)
{
	QueueItem *   qi;
	void *        item;

	if (qIsEmpty(q))
	{
		return NULL;
	}

	spin_lock(&(q->lock));

	qi = list_first_entry(&(q->list), QueueItem, list);

	item = qi->item;

	list_del(&(qi->list));

	kfree((void *) qi);

	spin_unlock(&(q->lock));

	return item;
}

int qIsEmpty(Queue *q)
{
	int   ret;
	spin_lock(&(q->lock));
	ret = list_empty(&(q->list));
	spin_unlock(&(q->lock));
	return ret;
}

void queueTest()
{
   Queue *   q;
   void *    item;

   q = qCreate();

   item = kmalloc(20, GFP_ATOMIC);
   qEnqueue(q, item);

   item = kmalloc(20, GFP_ATOMIC);
   qEnqueue(q, item);

   item = kmalloc(20, GFP_ATOMIC);
   qEnqueue(q, item);

   while(1)
   {
      if (qIsEmpty(q))
         break;

      item = qDequeue(q);
      kfree(item);
   }

   qDelete(q);

   return;
}




