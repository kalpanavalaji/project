#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<signal.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdlib.h>

sem_t *m1,*m2;
int odd=1,even=2,m,n;
void *t1(void *arg);
void *t2(void *arg);
int main()
{
	
	printf("enter m & n values\n");
	scanf("%d\n",&m);
	scanf("%d\n",&n);

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

	int ret=fork();
	if(ret==0)
	{
		printf("in child 1\n");
		printf("pid od child 1=%d\n",getpid());
		 t1(&n);
		printf("end of child\n");
	}
	else
	{
	printf("in parent\n");
	printf("pid of parent =%d\n",getpid());
	t2(&m);
	printf("end of parent\n");
	}
sem_close(m1);
sem_close(m2);
sem_unlink("/sync1");
sem_unlink("/sync2");
exit(0);
}


void *t1(void *arg)
{
 while(m || n) {

        sem_wait(m1);
        if(n == 0) goto l1;
        printf("%d\n",odd);
        odd=odd+2;
        n--;
/*      if((n==0)&&(m!=0))
        {
                exit(1);
        }*/
        l1:sleep(1);
        sem_post(m2);

 }
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
}
