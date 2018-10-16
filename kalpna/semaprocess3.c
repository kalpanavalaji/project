#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include<string.h>
#include<malloc.h>
#include <sys/sem.h>
int main()
    {
            int key,share_id,num;
            char *data;
            int semid;
            struct sembuf sb={0,-1,0};
            key=13;
            if(key == -1 ) {
                    printf("\n\n Initialization Falied of shared memory \n\n");
                    return 1;
            }
            share_id=shmget(key,1024,IPC_CREAT|0744);
            if(share_id == -1 ) {
                    printf("\n\n Error captured while share memory allocation\n\n");
                    return 1;
            }
            data=(char *)shmat(share_id,(void *)0,0);
            strcpy(data,"Testing string\n");
            if(!fork()) { //Child Porcess
                 sb.sem_op=-1; //Lock
                 semop(share_id,(struct sembuf *)&sb,1);

                 strncat(data,"feeding form child\n",20);

                 sb.sem_op=1;//Unlock
                 semop(share_id,(struct sembuf *)&sb,1);
                 Exit(0);
            } else {     //Parent Process
              sb.sem_op=-1; //Lock
              semop(share_id,(struct sembuf *)&sb,1);

               strncat(data,"feeding form parent\n",20);

              sb.sem_op=1;//Unlock
              semop(share_id,(struct sembuf *)&sb,1);

            }
            return 0;
    }
