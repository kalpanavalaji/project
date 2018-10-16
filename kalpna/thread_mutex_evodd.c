#include<stdio.h>
#include<pthread.h>
int num=0,m=6,n=6;
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;

void*thread1(void *x)
{
	
	
	pthread_mutex_lock(&mymutex);
	
	
	if(num%2==0)
	printf("%d",num);
	
	 else
	{
	 	pthread_cond_signal(&mycond);

		
		pthread_cond_wait(&mycond,&mymutex);
	 	//pthread_mutex_unlock(&mymutex);

	}
	
	num++;
	
	pthread_mutex_unlock(&mymutex);
	}
void* thread2(void *x)
	{

	
	pthread_mutex_lock(&mymutex);
	
	
		if(num%2==!0)
		printf("%d",num);
		else
		{
		
		pthread_cond_signal(&mycond);
		pthread_cond_wait(&mycond,&mymutex);
		}
		num++;
	
	pthread_mutex_unlock(&mymutex);
	}
int main()
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread1,0);
	pthread_create(&tid2,NULL,thread2,0);
	pthread_join(tid1,0);
	pthread_join(tid2,0);
}


