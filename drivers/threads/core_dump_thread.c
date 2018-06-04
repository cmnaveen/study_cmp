
/*
	when I create 4 threads it's like

	Before Thread 3 create
	After Thread 3 create
	Before Thread 2 create
	After Thread 2 create
	Before Thread 1 create
	After Thread 1 create
	Before Thread 0 create
	After Thread 0 create
	Before Thread 3 join
	After Thread 3 join
	Before Thread 2 join
	After Thread 2 join
	Before Thread 1 join
	After Thread 1 join
	Before Thread 0 join
Segmentation Fault(core dumped)

	I can't seem to find why.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

	pthread_mutex_t mutex_lock;

	struct arg_struct {
		int a;
		int b;
	};

void *t_function(void *data) {
	pthread_mutex_lock(&mutex_lock);

	struct arg_struct *arg = (struct arg_struct *)data;
	long int s;

	s = arg->a;

	pthread_mutex_unlock(&mutex_lock);

	return (void **)s;
}

int main()
{
	int i;

	pthread_t p_thread[7];
	int thr_id;
	int status;

	struct arg_struct arg[2];

	for(i = 1; i >= 0; i--) {
		arg[i].a = i;
		arg[i].b = i;
	}

	pthread_mutex_init(&mutex_lock, NULL);

	for(i = 6; i >= 0; i--) {
		printf("Before Thread %d create\n", i);
		thr_id = pthread_create(&p_thread[i],NULL, t_function, (void *)&arg[i]);
		printf("After Thread %d create\n", i);
		usleep(1000);
	}

	int temp[6];

	for(i = 6; i >= 0; i--) {
		printf("Before Thread %d join\n", i);
		pthread_join(p_thread[i], (void**)&status);
		printf("After Thread %d join\n", i);
		temp[i] = status;
	}

	printf("\n%d %d", temp[6], temp[5]);
	printf("%d %d", temp[4], temp[3]);
	printf("%d %d", temp[2], temp[1]);
	printf("%d \n", temp[0]);
	pthread_mutex_destroy(&mutex_lock);

	return 0;
}


