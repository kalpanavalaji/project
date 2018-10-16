#include<stdio.h>
#include<signal.h>
void handler(int signo)
{
	printf("signal:%d\n",signo);
}
int main()
{
	int fd[2];
	signal(SIGPIPE,handler);
	pipe(fd);
	close(fd[0]);
	int w=write(fd[1],"hello",6);
	if(w==-1)
	{
		perror("writee");
		exit(1);
	}
}
