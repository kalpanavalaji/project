#include<stdio.h>
#include<pthread.h>
void *fun1(void *);
int main()
{
	int ret;
	char *msg="hello";
	pthread_t mythread;
	printf("created thread\n");
	ret=pthread_create(&mythread,NULL,fun1,(void *)msg);
	if(ret==0)
	{
		printf("success");
	}
	else
	{
		printf("failure");
	}
	pthread_exit(NULL);
}
void *fun1(void *ptr)
{
	printf("within fun %x\n",pthread_self());
	printf("msg received from thread %s\n",(char *)ptr);
	pthread_exit(NULL);
}

