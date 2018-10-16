#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void sig_handler(int signum)

	{

	    printf("Received signal %d\n", signum);

	}

int main()

	{

	    signal(SIGTSTP, sig_handler);

	    sleep(5); // This is your chance to pr
	}
