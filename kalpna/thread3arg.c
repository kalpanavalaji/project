#include<stdio.h>
#include<pthread.h>
#include<string.h>
void *fun1(void *);
struct msg
{
	int uid;
	char data[5];
}m;
int main()
{
	int ret;
	pthread_t mythread;
	m.uid=100;
	strcpy(m.data,"hello");
	printf("uid in main:%d\n",m.uid);
	printf("created thread\n");
	ret=pthread_create(&mythread,NULL,fun1,(void *)&m);
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
	printf("uid:%d\n",((struct msg *)ptr)->uid);
	printf("msg from thread:%s\n",((struct msg *)ptr)->data);
	pthread_exit(NULL);
}

