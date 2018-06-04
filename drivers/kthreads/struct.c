#include<stdio.h>
#include<stdlib.h>

static char flag = 'n';
static DECLARE_WAIT_QUEUE_HEAD(wq);
struct queue
{
	//	struct d *p1;
	char  *p;
	struct queue *next;

}*front=NULL,*rear=NULL;

struct data
{

	int  x;

}*DP;


void push_queue(struct data *dp)
{
	printf("enter the data \n");
	scanf("%d",&(dp->x));
	printf("\n%d\n",(dp->x));
	struct queue *new =(struct queue *) malloc(sizeof(struct queue));
	//			new->p = (char *) malloc(10);
	new->p  =(char *) &(dp->x);
	new->next = NULL;
	if(front==NULL)
		front=rear=new;
	else
	{
		rear->next=new;
		rear=new;
	}
//wake_up_interruptible(&wq);

}

void pop_queue(struct queue *front)
{

wait_event_interruptible(wq,flag == 'y' );
flag = 'n';
	FILE *fp;
	char *ptr;
	fp = fopen("my_file","rb");
	//ptr = DP->x;

	if(front==NULL)
		printf("empty list");
	else
	{
		struct queue *temp = front;
		ptr = (temp->p->x);
		printf("pop %s\n",ptr);
		int size=sizeof(temp->p);
		fwrite(ptr, sizeof(ptr), size, fp); 
		front = front->next;

	}



}
void display()
{      
	printf("\n in dispaly\n");
	struct queue *temp = front;
	while(temp)
	{
		printf("\n in while\n");
		printf("%c",*(temp->p));
		temp = temp -> next;

	}


}
int main()
{
	int a,op,no_of_nodes,i;
	struct data *d = (struct data *)malloc (sizeof(struct data));
	while(1)
	{
		printf("1)push_queue\n2)pop_queue\n3)display\n4)exit\n");
		printf("enter the op:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				printf("\nno of node requied :");
				scanf("%d",&no_of_nodes);
				for(i=0;i<no_of_nodes;i++)
				{
					push_queue(d);

				}
				break;
			case 2:
				pop_queue(front);
				break;
			case 3:
				display();
				break;
			case 4:
				exit(0);

			default:
				printf("\nunknown op\n");
				break;
		}

	}
}
