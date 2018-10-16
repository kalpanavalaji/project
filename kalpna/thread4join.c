#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
void *fun1(void *);
void *fun2(void *);
void *fun3(void *);
int main()
{
	int ret1,ret2,ret3,i;
	pthread_t mythread1,mythread2,mythread3;
	void *st;
	char *msg="hello";
	for(i=0;i<5;i++)
{
	printf("created thread\n");
	ret1=pthread_create(&mythread1,NULL,fun1,(void *)msg);
//	pthread_join(&mythread,&st);
//	printf("status of terminated thread %s\n",(char *)st);
	
	if(ret1==0)
	{
		printf("success\n");
	}
	else
	{
		printf("failure");
		exit(1);
	}
//	 pthread_join(mythread1,&st);
//        printf("status of terminated thread %s\n",(char *)st);

 
	ret2=pthread_create(&mythread2,NULL,fun2,(void *)msg);
	if(ret2==0)
        {
                printf("success 2\n");
        }
        else

{
                printf("failure");
                exit(1);
        }
//	 printf("status of terminated thread %s\n",(char *)st);
//	 pthread_join(mythread2,&st);
  //      printf("status of terminated thread %s\n",(char *)st);


	
	ret3=pthread_create(&mythread3,NULL,fun3,(void *)msg);
	if(ret3==0)
        {
                printf("success 3\n");
        }
        else
        {
                printf("failure\n");
                exit(1);
        }
//	 printf("status of terminated thread %s\n",(char *)st);
	/* pthread_join(mythread1,&st);
        printf("status of terminated thread %s\n",(char *)st);

	
	 pthread_join(mythread2,&st);
        printf("status of terminated thread %s\n",(char *)st);

	 pthread_join(mythread3,&st);
        printf("status of terminated thread %s\n",(char *)st);*/




	i++;
}
	
}
void *fun1(void *ptr)
{
	printf("within fun %x\n",pthread_self());
	printf("msg received from thread:%s\n",(char *)ptr);
	pthread_exit("bye");
}
void *fun2(void *ptr)
{
        printf("within fun %x\n",pthread_self());
        printf("msg received from thread:%s\n",(char *)ptr);
        pthread_exit("byee");
}
void *fun3(void *ptr)
{
        printf("within fun %x\n",pthread_self());
        printf("msg received from thread:%s\n",(char *)ptr);
        pthread_exit("byeee");
}


