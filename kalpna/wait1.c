#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	//printf("helloworld\n");
	printf("pid=%d\n",getpid());
	int ret=fork();
	if(ret)
	{
		printf("===in parent====");
		printf("id=%d\n",getpid());
		printf("child id=%d\n",ret);
		int ret1=wait(0);
		printf("ret1=%d\n",ret1);
	}
	else
	{
		printf("====in child===\n");
		printf(" chid id=%d\n",getpid());
		printf("parent id=%d\n",getppid());
	}
}
