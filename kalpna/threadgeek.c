#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 

int g = 0;
 

void *myThreadFun(void *vargp)
{
    
    int myid = (int)vargp;
 
    
    static int s = 0;
 
   
    ++s; ++g;
 
 
    printf("Thread ID: %d, Static: %d, Global: %d\n", myid, ++s, ++g);
}
 
int main()
{
    int i;
    pthread_t tid[3];
 
    
    for (i = 0; i < 3; i++)
        pthread_create(&tid[i], NULL, myThreadFun,i);
 
    pthread_exit(NULL);
    
}
