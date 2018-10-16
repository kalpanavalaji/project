#include<stdio.h>
#include<fcntl.h>
#include<semaphore.h>           
#include<stdlib.h>       
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
void *t1(void *arg);
void *t2(void *arg);
void *t3(void *arg);
void *t4(void *arg);
sem_t s1,s2,s3,s4;
int no1,no2,no3,no4;
void sig_handler(int signum)
{
 printf("receive signal %d\n",signum);
//printf("before no 1\n");
 no1=1;
//printf("after no 1\n");

}
int main()
{
 	int result1,result2,result3,result4;
 	pthread_t th1,th2,th3,th4;
        sem_init(&s1,0,1);
        sem_init(&s2,0,0);
        sem_init(&s3,0,0);
        sem_init(&s4,0,0);
	signal(SIGINT,sig_handler);
	result1=pthread_create(&th1,NULL,t1,NULL);
	if(result1 == 0) {
 	printf("pthread 1 create successful\n");

}
	result2=pthread_create(&th2,NULL,t2,NULL);
	if(result2 == 0) {
 	printf("pthread 2 create successful\n");

}
	result3=pthread_create(&th3,NULL,t3,NULL);
	if(result3 == 0) {
 	printf("pthread 3 create successful\n");
 
}
	result4=pthread_create(&th4,NULL,t4,NULL);
	if(result4==0){
	printf("pthread 4 create successful\n");
	
}


pthread_join(th1,NULL);
pthread_join(th2,NULL);
pthread_join(th3,NULL);
pthread_join(th4,NULL);
/*printf("\nbefore signal handler\n");
sig_handler(SIGINT);
printf("\n after signal handler\n");*/



 sem_destroy (&s1);
 sem_destroy (&s2);
 sem_destroy (&s3);
 sem_destroy (&s4);

}



void *t1(void *arg)
{
 while(1) {
	sleep(1);	
	sem_wait(&s1);
	printf("1\n");
	sleep(1);
//	 signal(SIGINT,sig_handler);
	sem_post(&s2);
	if(no1==1)
	{
	no2=1;
	printf("signal 1 closeed\n");
//	sem_close(&s1);
	 sem_destroy (&s1);

	}
      
	}

pthread_exit(NULL);
}

void *t2(void *arg)
{
 
 while(1) {
	sem_wait(&s2);
	printf("2\n");
 	sleep(1);
//	 signal(SIGINT,sig_handler);
	sem_post(&s3);
	if(no2==1)
	{
	no3=1;
	printf("signal 2 closed\n");
//	sem_close(&s2);
	 sem_destroy (&s2);

	}
		
 }

pthread_exit(NULL);
}

void *t3(void *arg)
{
 while(1) {
	sem_wait(&s3);
	printf("3\n");
	sleep(1);
	 //sig_handler(SIGINT);
//	signal(SIGINT,sig_handler);
	sem_post(&s4);
	if(no3==1)
	{
	no4=1;
	printf("signal 3 closed\n");
//	sem_close(&s3);
	 sem_destroy (&s3);

	}
	
 }
pthread_exit(NULL);
}
void *t4(void *arg)
{
 while(1) {
        sem_wait(&s4);
        printf("4\n");
        sleep(1);
	//sig_handler(SIGINT);
//	signal(SIGINT,sig_handler);
        sem_post(&s1);
	if(no4==1)
	{
	printf("sinal 4 closed\n");
//	sem_close(&s4);
	 sem_destroy (&s4);

//	break;
	}
        }
pthread_exit(NULL);
 }


