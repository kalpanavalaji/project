#include<stdio.h>
int main()
{
	int fd[2];
	char buff[5];
	pipe(fd);
	read(fd[0],buff,5);
}
