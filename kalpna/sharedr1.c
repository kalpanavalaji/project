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
	printf("content in the shared memory 1 %d\n",i);

        }
        shmdt(ptr);
        }
        else
        perror("shmat");
}

