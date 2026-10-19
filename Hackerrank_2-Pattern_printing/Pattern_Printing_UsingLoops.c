#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int maxNum;
    printf("Enter the maximum number in the pattrn: ");
    scanf("%d", &maxNum);
  	
    for (int i=0; i<(2*maxNum-1); i++){
        for (int j=0; j < (2*maxNum -1); j++){
            
           int rowDist = abs(i-(maxNum-1));
           int colDist = abs(j-(maxNum-1));
           
           int maxdist;
           if( rowDist > colDist){
            maxdist = rowDist; }
           else
           maxdist = colDist;
           
           printf("%d", maxdist+1);
           if (j < (2*maxNum -2)) printf(" ");       
        }
        
        printf("\n");
    }
    return 0;
}