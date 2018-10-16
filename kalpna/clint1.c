#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
int main()
{
	char msg[40];
	 struct sockaddr_in server;
        int len=sizeof(server);

	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");
		exit(1);
	}
	else
	{
		server.sin_family=AF_INET;
        	server.sin_port=htons(8000);
        	server.sin_addr.s_addr=inet_addr("196.168.1.1");
		int c=connect(sfd,(struct sockaddr *)&server,len);
		if(c==-1)
		{
			perror("connecr");
			exit(1);
		}
		else
		{
		while(1)
		{
		
		printf("enter msg to server\n");
		fgets(msg,40,stdin);
		send(sfd,msg,40,0);
		printf("waiting for server msg\n");
                int n=recv(sfd,msg,40,0);
		if(n==-1)
		{
			perror("recv");
		}
		else
		{
		msg[n]='\0';
		printf("msg from server %s\n",msg);
		}
		}
	}
	}
	return 0;
}
