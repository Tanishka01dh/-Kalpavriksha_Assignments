#include<stdio.h>
#include<stdlib.h>
    int n;
    int i, j;
    int mat[10][10];
    int temp;

    void displaying(){       // prints the matrix
        for (i=0; i<n; i++){
            for(j=0; j<n; j++){
                printf(" %d", *(*(mat+i)+j));
            }
            printf("\n");
        }   }
    
    void rotation(){    // rotates the matrix by 90 deg
       for(i=0; i<n; i++){
        for(j= i+1; j<n; j++){   // transposing
            temp = *(*(mat +i)+j) ;      
            *(*(mat +i)+j) = *(*(mat +j)+i);
            *(*(mat +j)+i) = temp;    
        } 
    }
        for(i=0;i<n;i++){              // swapping left and right parts in each row
            int  *left = *(mat +i);
            int  *right = (*(mat+i)+ n-1);
            while(left < right){   
                temp = *left;
                *left = *right;
                *right = temp;
                left++;
                right--;
            }   
        } }

    void smoothing(){       // performs smoothing
        int sum, count;
        int r,c;
        int row,col;
        int avg;
        int *cell;

        for(i=0;i<n; i++){
            for(j=0;j<n;j++){
                sum=0; count =0;

                for( r=-1; r<=1; r++){      // checking for valid cells
                    for (c=-1; c<=1; c++){
                        row = i+r;
                        col = j+c;
                        if((row>= 0 && row<n) && (col>= 0 && col<n )){
                            sum += (*(*(mat+row)+col)) %256 ;  // adding all valid original cells
                            count++;    
                        }  }     
                }
                avg = sum/count;
                cell = (*(mat+i)+ j);
                *cell = avg* 256 + (*cell% 256);  }
        }
        for(i=0;i<n;i++){         // getting all the new smoothed values
            for(j=0;j<n;j++){
                cell = (*(mat+i)+j);
                *cell = *cell/256;
            }
        }
    }
    
    int main(){

    printf("\nEnter matrix size: \n");
    scanf("%d", &n);
    if (n<2 || n>10){
    printf("Invalid matrix size");
    return -1; }

    for (i=0;i<n; i++){
        for(j=0; j<n; j++){
            *(*(mat+i)+j) = rand() %256;
        }
    }
    printf("\n The original matrix is :\n");
    displaying();
    printf("\n The matrix rotated at 90 deg clockwise is :\n");
    rotation();
    displaying();
    printf("\n The matrix after smoothening is :\n");
    smoothing();
    displaying();
       
return 0;
}
