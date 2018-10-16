#include <stdio.h>
#include <stdlib.h>

int main() {
  int **p;
  int m, n, i, j;
  int l=m*n;

  printf("Enter number of rows and columns: ");
  scanf("%d%d", &m, &n);

  
  p = (int *) malloc(sizeof(int *) * m); 
  for(i = 0; i < m; i++) {
    p[i] = (int) malloc(sizeof(int) * n); 
  }


 int disp[m][n];
   
  
   for(i=0; i<m; i++) {
      for(j=0;j<n;j++) {
         printf("Enter value for disp[%d][%d]:", i, j);
         scanf("%6d", &disp[i][j]);
      }
   }
   //Displaying array elements
   printf(" Dimensional array elements:\n");
   for(i=0; i<m; i++) {
      for(j=0;j<n;j++) {
         printf("%6.2d ", disp[i][j]);
         if(j==m){
            printf("\n");
	 printf("%6.2d ", disp[i][j]);
    }
    printf("\n");
  }

  for(i = 0; i < m; i++) {
    free(p[i]); 
  }
  free(p); 

         
      
}   
   return 0;
}


