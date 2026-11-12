#include<stdio.h>
#include<stdlib.h>

int hourglassSum(int arr_rows, int arr_columns, int** arr) {

    int i, j, r, c;
    int maxsum = arr[0][0]+ arr[0][1]+ arr[0][2]+ arr[1][1]+ arr[2][0] + arr[2][1] + arr[2][2];

    for(i = 0; i < arr_rows-2; i++) {
        for(j = 0; j < arr_columns-2; j++) {
            int sum = 0;
            for(r = i; r < i+3; r++) {
                for(c = j; c < j+3; c++) {

                    if(r == i+1 && (c == j || c == j+2)) {
                        continue;}
                    sum += arr[r][c];
                }
            }
            if(sum > maxsum) {
                maxsum = sum; }
        }
    }
    return maxsum;
}

int main(){

    int **arr = calloc(6,sizeof(int *));
    if(arr == NULL) {
    printf("Memory allocation failed");
    return 1;
    }
    for(int i = 0; i < 6; i++) {
        arr[i] = calloc(6, sizeof(int));
        if(arr[i] == NULL) {
        printf("Memory allocation failed");
        return 1;
        }
    }

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    int result = hourglassSum(6,6,arr);
    printf("%d", result);

    for(int i = 0; i < 6; i++) {
        free(arr[i]); }
    free(arr);
    return 0;
}

