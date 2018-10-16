#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,rem,temp,sum=0;
	printf("Enter two digit number");
	scanf("%d",&n);
	temp=n;
	while(temp>0)
	{
		rem=temp%10;
		sum=sum+rem;
		temp=temp/10;

	}
	if(n==(sum*3))
		printf("it is a Peculiar two digit number\n");
	else
		printf("not a Peculiar two digit number\n");

} 
