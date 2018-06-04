#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
void *print_msg_fun(void *ptr);

main()
{
	pthread_t thread1,thread2;
	char *msg1 = "thread 1";
	char *msg2 = "thread 2";
	int iret1,iret2;
	/* Create independent threads each of which will execute function */
	iret1 = pthread_create(&thread1,NULL,print_msg_fun, (void *) msg1);
	iret2 = pthread_create(&thread2,NULL,print_msg_fun, (void *) msg2);

	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	printf("thread1 return:%d\n",iret1);
	printf("thread2 return:%d\n",iret2);

	exit(0);

}
void *print_msg_fun(void *ptr)
{
	char *msg;
	msg = (char *) ptr;
	printf("%s \n",msg);


}
