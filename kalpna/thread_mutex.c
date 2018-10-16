#include<stdio.h>
#include<pthread.h>
int num=1;
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;

void*thread1(void *x)
{
	printf("In thread1\n");
	pthread_mutex_lock(&mymutex);
	if(num!=5)
	pthread_cond_wait(&mycond,&mymutex);
	printf("signal caught\n");
	sleep(1);
	printf("in thtread 1\n");
	pthread_mutex_unlock(&mymutex);
	printf("exiting thread 1");
	}
void* thread2(void *x)
	{
	int i;
	printf("in thread 2\n");
	pthread_mutex_lock(&mymutex);
	for(i=0;i<5;i++)
	{
		num=num+1;
		printf("%d\n",num);
		if(num==6)
		pthread_cond_signal(&mycond);
		sleep(1);
		printf("in thread 2\n");
		}
	pthread_mutex_unlock(&mymutex);
	printf("exiting thread2\n");
	}
int main()
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread1,0);
	pthread_create(&tid2,NULL,thread2,0);
	pthread_join(tid1,0);
	pthread_join(tid2,0);
}


