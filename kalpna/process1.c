#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
int odd=1,even=2,m,n,ret;
void t1(int);
void t2(int);
int main()
{
	
	printf("enter m & n values\n");
	scanf("%d\n",&m);
	scanf("%d\n",&n);
	 ret=fork();
	if(ret==0)
	{
		printf("in child 1\n");
		printf("pid od child 1=%d\n",getpid());
		 t1(n);
		printf("end of child\n");
	}
	else
	{
	printf("in parent\n");
	printf("pid of parent =%d\n",getpid());
	t2(m);
	printf("end of parent\n");
	}
}


void t1(int n)
{
        int i=0;
        for(i=0;i<=n;i++)
        {
                if(n%2==0)
                {
                printf("%d\n",n);
                }

                n--;
        }
        if(n==0&m!=0)
        kill(ret,SIGKILL);

        sleep(1);
        exit(1);
}


void t2(int m)
{
	int i=0;
	for(i=0;i<=m;i++)
	{
		if(m%2!=0)
		{
		printf("%d\n",m);
		}
		
		m--;
	}
	if(m==0&n!=0)
	kill(ret,SIGKILL);
	
	sleep(1);
	exit(1);
}
