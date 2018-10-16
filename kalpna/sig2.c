#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
void my(int);
int main()
{
	signal(SIGCHLD,my);
	int ret=fork();
	if(ret==0)
	{
	printf("===child====");
	printf("pid of child %d\n",getpid());
	exit(2);
	}
	else
	{
//		sleep(1);
		printf("===parent===");
		printf("pid of parent %d\n",getpid());
		wait(0);
	}
}
void my(int a)
{
	printf("entered my handler\n");
	printf("signal receivedv %d\n",a);
	printf("id=%d\n",getpid());
}
	
