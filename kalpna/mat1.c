#include <stdlib.h>
#include<stdio.h>
 
 
int main(int argc, char *argv[]) {
 
 int *piBuffer = NULL; //pointer to integer
 
 int nBlock = 0; //Variable store number of block
 
 int iLoop = 0; //Variable for looping
 
 
 
 printf("\nEnter the number of block = ");
 
 scanf("%d",&nBlock); //Get input for number of block
 
 
 piBuffer = (int *)malloc(nBlock * sizeof(int));
 
 //Check memory validity
 if(piBuffer == NULL)
 {
 return 1;
 }
 
 //copy iLoop to each block of 1D Array
 for (iLoop =0 ; iLoop < nBlock ; iLoop++)
 {
 piBuffer[iLoop] = iLoop;
 }
 
 //Print the copy data
 for (iLoop =0 ; iLoop < nBlock ; iLoop++)
 {
 printf("\npcBuffer[%d] = %d\n", iLoop,piBuffer[iLoop]);
 }
 
 free(piBuffer); // free allocated memory
 
 return 0;
}
