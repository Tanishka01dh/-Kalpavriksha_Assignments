#include<stdio.h>
#include<stdlib.h>

void countSort(int arr_rows, int arr_columns, char*** arr) {
    int *count = calloc(100,sizeof(int));
    int* output = malloc( arr_rows*sizeof(int));
    if(count == NULL || output == NULL) {
        free(count);
        free(output);
        return;
    }
    
    for(int i =0;i<arr_rows;i++){
       int key = atoi(arr[i][0]);
        count[key]++;
    }
    
    for(int i = 1; i < 100; i++){
        count[i] = count[i] + count[i - 1];
    }
    
     for(int i = arr_rows - 1; i >= 0; i--){
        int key = atoi(arr[i][0]);
        output[count[key] - 1] = i;
        count[key]--;
    }
    
    for(int i = 0; i < arr_rows; i++){

        if(output[i] < arr_rows / 2){
            printf("-");
            printf(" ");}
        else{
            printf("%s", arr[output[i]][1]);
            printf(" ");}
    }
    free(count);
    free(output);
}

int main(){

    int arr_rows;
    scanf("%d", &arr_rows);

    char ***arr = malloc(arr_rows * sizeof(char **));
    if(arr == NULL)
        return 1;

    for(int i = 0; i < arr_rows; i++){
       
        arr[i] = malloc(2 * sizeof(char *));
        if(arr[i] == NULL)
            return 1;

        arr[i][0] = malloc(3 * sizeof(char));
        arr[i][1] = malloc(101 * sizeof(char));

        if(arr[i][0] == NULL || arr[i][1] == NULL)
            return 1;

        scanf("%2s %100s", arr[i][0], arr[i][1]);
    }

    countSort(arr_rows, 2, arr);

    for(int i = 0; i < arr_rows; i++){
        free(arr[i][0]);
        free(arr[i][1]);
        free(arr[i]);
    }
    free(arr);
    return 0;
}

