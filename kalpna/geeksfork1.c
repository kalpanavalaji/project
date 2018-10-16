#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

int main()
{
	// Creating first child
	int n1 = fork();
	printf("hello world");
	int n2 = fork();

	if (n1 > 0 )
	{
		printf("parent1\n");
		printf("%d  \n", n1);
		printf(" my id is %d \n", getpid());
		printf(" my parentid is %d \n", getppid());
	}
	else if (n2 > 0 )
	{
		printf("parent2\n");
		printf("%d  \n", n2);
		printf(" my id is %d \n", getpid());
		printf(" my parentid is %d \n", getppid());
	}

	else if (n1 == 0)
	{
		printf("First child\n");
		printf("%d  \n", n1);
		printf("my id is %d  \n", getpid());
		printf(" my parentid is %d \n", getppid());
	}

	else //if(n2 == 0)
	{
		printf("second child\n");
		printf("%d  \n", n2);
		printf("my id is %d  \n", getpid());
		printf(" my parentid is %d \n", getppid());
	}
}
/*parent1
7932  
 my id is 7931 
 my parentid is 6254 
parent1
7932  
parent2
 my id is 7933 
 my parentid is 2003 
7934  
First child
 my id is 7932 
 my parentid is 2003 
0  
my id is 7934  
 my parentid is 7932*/

