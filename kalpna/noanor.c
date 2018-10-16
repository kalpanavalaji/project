#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
	int pid=fork();
	if(pid==0)
	{
		printf("pid if child=%d\n",getpid());
		printf("pid of parent=%d\n",getppid());
		sleep(3);
		printf("pid ofm parent after sleep=%d\n",getppid());
		int a;
		printf("enter a\n");
		int r=scanf("%d",&a);
		if(r<0)
		perror("scanf");
		else
		{
		printf("val of r= %d\n",r);
		printf("a=%d\n",a);
		exit(7);
		}
	}
	else
	{
		int s;
		printf(" pid of parent in parent context =%d\n",getpid());
		int wait_id=wait(&s);
		printf(" add of s %d\n",(s>>8)&0x000000ff);
		if(wait_id<0)
		perror("wait");
		else
		{
		printf("wait_id=%d",wait_id);
		}
		if(WIFEXITED(s))
		{
			printf("normal\n");
			printf("status=%d",WEXITSTATUS(s));
		}
		else
		{
			printf("abnormal\n");
			printf("staus=%d\n",s);
		}
	}


return (0);
}

