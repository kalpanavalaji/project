#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
    
    printf("Printing GeeksQuiz from Thread \n");
//    return NULL;
	pthread_exit(NULL);
}
  
int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
	printf("before pthrad\n");
	pthread_exit(NULL);
	printf("after pthread\n");
    //exit(0);
}
