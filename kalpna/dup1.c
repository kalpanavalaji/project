#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
	int fd,ret;
	mknod("myfifo",S_IFIFO|0666,0);
	fd=open("myfifo",O_WRONLY);
	if(fd<0)
	perror("");
	ret=dup2(fd,1);
	if(ret==-1)
	{
	perror("");
	exit(1);
	}
	execlp("ls","ls","-l",0);
}
