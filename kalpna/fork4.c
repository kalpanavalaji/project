#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	int pid=fork();
	int a=10,b=20,c,d,e;
	if(pid==0)
	{
	 
   

        //      int status,ret;
//              int i=waitpid(-1,&status,0);
//              printf("ret=%d\n",i);
                printf("in child\n");
                e=a*b;
                printf("mul of two values=%d\n",e);

        }
	else
{
//	sleep(1);
	printf("===in parent====");
	printf("pid of parent=%d\n",getpid());
	printf("gid of parent =%d\n",getpgrp());
	c=a+b;
	printf("addition of two values=%d\n",c);
	}
}
