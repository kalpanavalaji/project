#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
//int a;
void forkexample()
{
	int a;
	if(fork()==0)
	{
	a=a+5;
	printf("%d %d\n",a,&a);
	}
	else
	{
	a=a-5;
	printf("%d %d\n",a,&a);
	}
}
int main()
{
	forkexample();
	return 0;
}
