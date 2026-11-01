#include<stdio.h>
#include<stdlib.h>

int surfaceArea(int A_rows, int A_columns, int A[100][100]) {   // calculates the surface area
 
    int area =0;
    for (int i=0;i<A_rows;i++){        //for left and right faces
        area += A[i][0]+ A[i][A_columns - 1];
    }
    for (int j=0;j<A_columns;j++){    // for front and back faces
        area += A[0][j]+ A[A_rows-1][j];
    }
    for(int i =0;i<A_rows; i++){    
        for(int j=0;j<A_columns;j++){
                if (A[i][j] != 0) {          // for top & bottom faces
                    area +=2; }
                
                if (j < A_columns - 1){
                   if (A[i][j]>A[i][j+1] || A[i][j]<A[i][j+1]){     // for difference of height row wise
                    int diff = abs(A[i][j] - A[i][j+1]);
                    area += diff; }
                }
                if (i < A_rows - 1){
                if (A[i][j]>A[i+1][j] || A[i][j]<A[i+1][j]){      // for diff of heights col wise
                    int diff = abs(A[i][j] - A[i+1][j]);
                    area += diff; }
                }    
        } }
        return area;
}

int main(){
    int A_row, A_column;
    scanf("%d %d", &A_row, &A_column);
    int A[100][100];
    for (int i=0;i<A_row;i++){
        for(int j =0;j<A_column;j++){
            scanf("%d", &A[i][j]);
        }
    }
    int result = surfaceArea(A_row, A_column, A);
    printf("\n%d",result);
    return 0;  
}