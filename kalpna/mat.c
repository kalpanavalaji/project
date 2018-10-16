#include<stdio.h>
#include<stdlib.h>
int main(){
	int m,n,i,j;
	printf("enter no of cols&rows\n");
	scanf("%d %d\n");
	int **array;
array = malloc(m * sizeof(int *));
if(array == NULL)
    {
    fprintf(stderr, "out of memory\n");
    exit(EXIT_FAILURE); //or return here
    }
for(i = 0; i < n; i++)
    {
    array[i] = malloc(n * sizeof(int));
    if(array[i] == NULL)
        {
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE); //or return here
        }
    }
/*	int **arr = malloc(m*sizeof(int*));
	for(i=0; i<m; i++){ 
	*arr[i] = malloc(n*sizeof(int));
*/	}
	printf("Enter value for dis");
   for(i=0; i<m; i++) {
      for(j=0;j<n;j++) {
        // printf("Enter value for disp[%d][%d]:", i, j);
         scanf("%d", &arr[i][j]);
      }
   }
   //Displaying array elements
   printf("Two Dimensional array elements:\n");
   for(i=0; i<m; i++) {
      for(j=0;j<n;j++) {
         printf(" %d ", arr[i][j]);
         }
            printf("\n");
         }
      
   
   return 0;
}
