#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main()
{
int M,N,i,j,l,m;
int sum=0,temp=0,temp1=0;
 l=0;
 m=0;

 printf("enter row&col size of matrix:1ton\n");
 scanf("%d %d" ,&M,&N);
 int **arr = (int**) malloc(M*sizeof(int*));

 for(int l=0;l<M;l++)
  {
 *(arr+l) = (int*)malloc(N*sizeof(int));
  }	
 printf("enter elements of matrix");

 for(int l=0;l<M;l++)                   
        {
         for(int m=0;m<N;m++)
	  {
		
	scanf("%d",&arr[l][m]);
 	  }
	}

if((M%3))
	{
 	i = M+(3-(M%3));
 	}
 	else
 	{
 	i = M;
 	}

if((N%3))
	{
 	j = N+(3-(N%3));
 	}
 	else
 	{
 	j = N;
 	}

if(i > M) 
{
for(m=0;m<j;m++)
{	 
for( int l=M;l<i;l++)
{
	 
		 *(*(arr+l)+m) = 1;
}	 
}
}
if(j >N)
{
	for(l=0;l<i;l++)
	{
        for( int m=N;m<j;m++)
	{
	  
	  *(*(arr+l)+m) = 1;
	  
	}
}
}

for(int l=0;l<i;l++)
{
for(int m=0;m<j;m++)
{
 printf("  %d  " ,arr[l][m]);
}
printf("\n");
}
sum =0;
if(i==j)
{
for( l=0;l<i;l++)
{
        for( m=0;m<j;m++)
        {

                if(l==m)
                {
                sum = sum+ arr[l][m];
                }



        }

}
printf("\ndiagonal  sum is:%d\n" ,sum);

sum =0;
l=0;
for( m=j-1;m>=0;m--)
{
                sum = (sum+arr[l++][m]);
		//l++;

}
printf("\n antidiagonal sum is:%d\n" ,sum);

}
sum =0;
l=0;
m=0;
 while(l < i || m< j )
 {
	for(l=temp;l<i;l++)	
	{
		for( m=temp1;m<j;m++)
		{
			sum = (sum+ arr[l][m]);
               	if( ( (j+1) % 3 )== 0)
		{
	        	break;
		}

		}
              
               if(( (l+1) % 3 )== 0)
		{
			 printf("\nsum is :%d \n" ,sum);
			sum=0;
                	if( (m+1) < j)
                	{
		 	temp1 = (temp1+3);
                	}
			else
			{
                 
			temp = (temp + 3);
                	temp1= 0;
			}
       			break; 
                }
	}		
}


}


