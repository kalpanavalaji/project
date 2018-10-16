#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
struct my_mess
{
	int mess_type;
	char mess_data[20];
	
};
int main()
{
	key_t key=10;
	struct msqid_ds mybuff;
	int my_id=msgget(key,IPC_CREAT|0666);
	if(my_id==-1)
	perror("");
	else
	{
	struct my_mess snd_mss;
	snd_mss.mess_type=5;
	strcpy(snd_mss.mess_data,"hello");
	msgsnd(my_id,&snd_mss,sizeof(snd_mss.mess_data),IPC_NOWAIT);
	msgsnd(my_id,&snd_mss,sizeof(snd_mss.mess_data),IPC_NOWAIT);
	int m=msgctl(my_id,IPC_STAT,&mybuff);
	if(m==-1)
	perror("");
	else
	{
	printf("no of mess=%d\n",mybuff.msg_qnum);
	printf("no of bytes=%d\n",mybuff.msg_qbytes);
	printf("no of permissions =%d\n",mybuff.msg_perm.mode);
	}
}
mybuff.msg_perm.mode=0775;
msgctl(my_id,IPC_STAT,&mybuff);
printf("no of permission=%o\n",mybuff.msg_perm.mode);
msgctl(my_id,IPC_RMID,0);
	
}
