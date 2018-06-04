#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<stdlib.h>

int no_of_threads = 3;
int count = 2;
char *message = "naveen reddy";

void *new_thread(void *arg)
{

	/*this is routine of thread define what the thread does*/
	int i;
	for(i=0 ; i<count ;i++){
		printf("%s\n",message);
		sleep(1);
	}/*thread terminates */

	pthread_exit("thank you for CPU time\n");
}

int main()
{
	pthread_t thread;
	int i;
	void *thread_result;
	for(i=0 ; i<no_of_threads ;i++)
	{

		/*create number of threads*/
		if(pthread_create(&thread,NULL,new_thread,(void*)message))
		{
			printf("error creating a new thread\n");
			exit(1);
		}
		/*wait for this thread to terminate */
		pthread_join(thread,&thread_result);
		/*print out terminate information */
		printf("%s\n",(char*)thread_result);
	}
	exit(EXIT_SUCCESS);
}


