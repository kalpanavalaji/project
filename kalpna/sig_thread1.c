#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
void sig_hand(int no)                  //signal handler
{
    printf("handler executing...\n");
    getchar();
}

void* thread1(void *arg1)              //thread1 
{
//	signal(2, sig_hand);
    while(1) {
            printf("thread1 active\n");
            sleep(1);
    }
}

void * thread2(void * arg2)           //thread2
{
  //  signal(2, sig_hand);
    while(1) {
    printf("thread2 active\n");
    sleep(3);
    }
}

int main()
{
    pthread_t t1;
    pthread_t t2;
	signal(2, sig_hand);
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    while(1);
//	signal(2, sig_hand);
}
