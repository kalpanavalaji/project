#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
int main()
{
	char msg[40];
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in server,clint;
	server.sin_family=AF_INET;
	server.sin_port=htons(8000);
	server.sin_addr.s_addr=INADDR_ANY;
	int len=sizeof(server);
	int b=bind(sfd,(struct sockaddr *)&server,len);
	if(b==-1)
	{
		perror("bind");
		exit(1);
	}
	int l=listen(sfd,1);
	if(l==-1)
	{
		perror("listen");
		exit(1);
	}
	int len1=sizeof(clint);
	while(1)
	{
	int cfd=accept(sfd,(struct sockaddr *)&clint,&len1);
	if(cfd==-1)
	{
		perror("accept");
		exit(1);
	}
	printf("waiting for connection\n");
//	printf("got connection from clint %s\n",inet-ntoa(clint.sin_addr));
	while(1)
	{
	printf("waiting msg from clint\n");
	int n=recv(cfd,msg,40,0);
	msg[n]='\0';
	printf("msg from clint %s\n",msg);
	printf("write to clint");
	fgets(msg,40,stdin);
	send(cfd,msg,40,0);
	}
}
return 0;
}
