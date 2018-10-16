#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("hello\n");
	int ret;
	ret=fork();
	if(ret==0)
	{
	execlp("cal","cal",(int*)0);
	}
//	ret=fork();
//	if(ret==0)
	else
	{
	execlp("date","date",(int*)0);
}
}
