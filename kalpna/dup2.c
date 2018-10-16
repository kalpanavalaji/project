#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd=open("myfifo",O_RDONLY);
	dup2(fd,0);
	execlp("grep","grep","thread",NULL);
}
	
