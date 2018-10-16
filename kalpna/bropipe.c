#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
//void handler(int signo);
int main()
{
        int ret;
	int fd[2],w,r,cnt=0;
	char buff[10];
//	signal(SIGPIPE,handler);
	ret = pipe(fd);
        if(ret == -1){
		printf("unable to opn pipe\n");
		exit(1);
 	}
	close(fd[0]);
	
	while((w=write(fd[1],'1',1)) != 1){
	printf(" cnt = %d\n",++cnt);
	}

if(w==-1)
	{
		perror("write");
		exit(1);
	}

	  r=read(fd[0],buff,10);
	printf("i am reading %s",buff);

}
/*
void handler(int signo)
{	
	printf("signal:%d\n",signo);
}
*/	
