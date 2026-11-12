#include<stdio.h>
#include<stdlib.h>

long arrayManipulation(int n, int queries_rows, int queries_columns, int queries[queries_rows][3]) {
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
    int (*queries)[3] = malloc(q * sizeof(*queries));

    if (queries == NULL) {
        return 1;
    }
    for(int i=0;i<q;i++){
        for(int j =0;j<3;j++){
        scanf("%d", &queries[i][j]);}
    }
    long result = arrayManipulation(n,q,3,queries);
    printf("%ld", result);
    free(queries);
    return 0;
}