#include<stdio.h>
#include<pthread.h>
#include<fcntl.h>          
#include<semaphore.h>
#include<stdlib.h>
#include<signal.h>

sem_t *m1,*m2;
int odd=1,even=2,n=2,m=4;

void *t1(void *arg)
{
 while(m || n) {
	
	sem_wait(m1);
	if(n == 0) goto l1;
	printf("%d\n",odd);
	odd=odd+2;
	n--;
/*	if((n==0)&&(m!=0))
	{
		exit(1);
	}*/
	l1:sleep(1);
	sem_post(m2);
       
 }

pthread_exit(NULL);
}

void *t2(void *arg)
{
 
 while(m || n) {
	sem_wait(m2);
	if(m == 0) goto l2;
	printf("%d\n",even);
	even=even+2;
	m--;
	/*if((m==0&&n!=0))
	{
		exit(1);
	}*/
 	l2:sleep(1);
	sem_post(m1);
		
 }


pthread_exit(NULL);
}


int main()
{

 pthread_t th1,th2;
	
 
m1 = sem_open("/sync1", O_CREAT|O_EXCL, S_IRUSR | S_IWUSR, 1); 
if(m1 == SEM_FAILED) {
 	perror("sem_open1");
	exit(1);
}
 
m2 = sem_open("/sync2", O_CREAT|O_EXCL, S_IRUSR | S_IWUSR, 0); 
if(m2 == SEM_FAILED) {
 	perror("sem_open2");
	exit(1);
}
 
 
pthread_create(&th1,NULL,t1,NULL);

pthread_create(&th2,NULL,t2,NULL);

pthread_join(th1,NULL);  
pthread_join(th2,NULL);    
sem_close(m1);
sem_close(m2);
sem_unlink("/sync1");
sem_unlink("/sync2");

exit(0);
}


