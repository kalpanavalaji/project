#include<stdio.h>
int main()
{
	int fd[2];
	int p=pipe(fd);
	if(p==-1)
	{
	perror("pipe");
	exit(1);
	}
	printf("fd[0]:%d\tfd[1]:%d\n",fd[0],fd[1]);
}
