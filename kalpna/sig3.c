#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int main()
{
	int myid=fork();
	if(myid==0)
	{
	sleep(1);
	printf("=child==\n");
	printf("pid of child %d\n",getpid());
	 kill(myid,9);
	sleep(5);
	printf("after sleep\n");
	}
	else
	{
	//sleep(3);
	printf("==in parent==\n");
//	wait(0);
//	kill(myid,SIGCHLD);
	}
}

