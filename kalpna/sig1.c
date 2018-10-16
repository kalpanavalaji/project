#include<stdio.h>
#include<signal.h>
void handle_sigint(int sig);
int main()
{
	signal(SIGINT,handle_sigint);
	while(1)
	{
	
		printf("hello world\n");
		sleep(1);
	//	 while(1);
	}
	return 0;
}
void handle_sigint(int sig)
{
	int a=10,b=7;
	printf("addition %d\n",a+b);
	printf("Caught signal %d\n", sig);
	
}
