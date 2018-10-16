#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
	int ret,r,fd;
	char buff[5];
	ret=mknod("mypipe",S_IFIFO|0666,0);
	if(ret==-1)
	{
		perror("mknod");
		exit(1);
	}
	else
	{
	fd=open("mypipe",O_RDONLY);
	printf("fd=%d\n",fd);
	r=read(fd,buff,sizeof(buff));
	buff[r]='\0';
	printf("content from pipe:%s\n",buff);
	}
}


