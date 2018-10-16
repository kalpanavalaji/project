#include<stdio.h>
#include<pthread.h>

volatile int num=1;
int m=6,n=6;
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;

void*thread1(void *x)
{
	while() {
	pthread_mutex_lock(&mymutex);
	
	printf("in");       	
	if(num%2==0)
	{
	printf("%d  ",num);
	num++;
	m--;
	// pthread_cond_wait(&mycond,&mymutex);
	
	}
	
	//pthread_cond_wait(&mycond,&mymutex);
	
	else
		{
//		printf("in else...");
		printf("%d  ",num);
		num++;
		n--;
	//	pthread_cond_signal(&mycond);
	//	pthread_cond_wait(&mycond,&mymutex);
		}	
        sleep(1);	
	pthread_mutex_unlock(&mymutex);
	
//	sleep(1);
	}
}
	
	
int main()
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread1,0);
	pthread_create(&tid2,NULL,thread1,0);
	pthread_join(tid1,0);
	pthread_join(tid2,0);
}


