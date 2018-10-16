/*#include<stdio.h>
#include<stdlib.h>

int main()
{
char a='h';
 int p[2]={0};
 int cnt=0;
 int ret;
 close(p[0]);
// while(1) {

 	while(ret=write(p[1],&a,1)!=1){
//f(ret != 1) break;
	cnt++;
	printf("%d\n",cnt);
}

 }*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(void)
{
    int tube[2];
    char c = 'c';
    int i;

    fprintf(stdout, "Tube Creation\n");
    fprintf(stdout, "Theoretical max size: %d\n", PIPE_BUF);
    
if( pipe(tube) != 0)
    {
        perror("pipe");
        _exit(1);
    }
    fprintf(stdout, "Writing in pipe\n");
    for(i=0;; i++)
    {
        fprintf(stdout, "%d bytes written\n", i+1);
        if( write(tube[1], &c, 1) != 1)
        {
            perror("Write");
            _exit(1);
        }
    }
    return 0;
}
