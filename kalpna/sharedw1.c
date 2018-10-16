#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
int main()
{
	key_t key=200;
	int shmid=shmget(key,50,IPC_CREAT|0666);
	int *ptr=(int*)shmat(shmid,NULL,0);
	if(ptr)
	{	
	int i;
	for(i=0;i<5;i++)
	{
	*ptr=i;
	ptr++;

	}
	shmdt(ptr);

	}
	else
	perror("shmat");
}
