#include<stdio.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<sys/shm.h>
int main()
{
	int key1=11,ret;
	int semid=semget(key1,1,IPC_CREAT|0666);
	if(semid==-1)
	{
	perror("semget");
	}
else
	{
	ret=semctl(semid,0,SETVAL,1);
	if(ret==-1)
	{
	perror("semctl");
	}
	else
	{
	struct sembuf x={0,-1,0};
	ret=semop(semid,&x,1);
	if(ret==-1)
	{
	perror("semop");
	}
	else
	{
		printf("locked");
		key_t key=100;
		int shmid=shmget(key,50,IPC_CREAT|0666);
		if(shmid==-1)
		perror("shmget");
		else
		{
		printf("shmid=%d\n",shmid);
		int *ptr=(int*)shmat(shmid,NULL,0);
		if(ptr)
	    {
		int i;
		for(i=0;i<5;i++)
		{
			printf("contents=%d\n",*ptr);
			ptr++;
		}
		sleep(20);
		shmdt(ptr);
		semctl(semid,0,SETVAL,1);
	}
	else
	perror("shmat");
	}
	}
	}
}
}

