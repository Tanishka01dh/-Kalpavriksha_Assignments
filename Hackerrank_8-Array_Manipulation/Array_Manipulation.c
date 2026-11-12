#include<stdio.h>
#include<stdlib.h>

long arrayManipulation(int n, int queries_rows, int queries_columns, int** queries) {
    long *arr = calloc(n+2,sizeof(long));
       if (arr == NULL) {
        return 0;
    }   
    long sum =0;
    long maxvalue=0;
    for(int i =0;i<queries_rows;i++){
        int a = queries[i][0];
        int b = queries[i][1];
        int k = queries[i][2];
             
            arr[a] += k;
            arr[b + 1] -= k;
    }
    for(int i=1;i<=n;i++){
        sum += arr[i];
        if (sum>maxvalue){
            maxvalue = sum;
        }
    }
free(arr);   
return maxvalue;
}

int main(){
    int n,q;  
    scanf("%d",&n);
    scanf("%d",&q);
    int **queries = malloc(q * sizeof(int*));
    if (queries == NULL) {
    printf("Memory allocation failed\n");
    return 1;
}

    for(int i=0;i<q;i++){
        queries[i] = malloc(3 * sizeof(int));
        scanf("%d %d %d", &queries[i][0],
                      &queries[i][1],
                      &queries[i][2]);
    }

    long result = arrayManipulation(n,q,3,queries);
    printf("%ld", result);

    for(int i = 0; i < q; i++) {
        free(queries[i]);
    }
    free(queries);
    return 0;
}

