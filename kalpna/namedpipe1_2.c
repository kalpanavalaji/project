#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
	int fd,w;
	fd=open("mypipe",O_WRONLY);
	printf("fd=%d\n",fd);
	w=write(fd,"HELLO",5);
	printf("number of bytes written into the pipe:%d\n",w);
}
