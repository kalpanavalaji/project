#include<stdio.h>
#include<unistd.h>
int main()
{
//	execlp("date","date",NULL);
	//execl("/bin/date","date",NULL);
//	printf("hello\n");
	char *a[]={"ls","-l",NULL};
	execvp("ls",a);
	
}

