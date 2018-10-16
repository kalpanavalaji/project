#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	int pid=fork();
	int a=10,b=20,c,d,e;
	if(pid==0)
	{
	sleep(1);
	printf("===in child1====");
	printf("pid of child1=%d\n",getpid());
	printf("gid of child1 =%d\n",getpgrp());
	c=a+b;
	printf("addition of two values=%d\n",c);
	exit(5);
	}
	else
	{
		int pid1=fork();
		if(pid1==0)
		{

		sleep(2);
                printf("====in child2===\n");
                printf("pid of child2=%d\n",getpid());
                printf("gid of child2=%d\n",getpgrp());
                d=b-a;
                printf("sub of two values=%d\n",d);
		
                }
		else
		{
		int status,ret;
		printf("parent goes to wait state");
		int i=waitpid(-1,&status,0);
		//int i;
		//int wait_id=wait(&i);
		
		printf("ret=%d\n",i);
		e=a*b;
		printf("mul of two values=%d\n",e);
		
		printf("in parent \n");
		printf("gid of parent %d\n",getpgrp());


		}

}
}




