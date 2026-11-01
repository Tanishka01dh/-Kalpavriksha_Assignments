#include<stdio.h>
#include<string.h>

int* matchingStrings(int stringList_count, char stringList[][100], int queries_count, char queries[][100], int* result_count) {
    
        static int result[1000];
        *result_count = queries_count;
        for (int i=0;i< queries_count;i++){
            int count=0;
            for(int j =0; j< stringList_count;j++){
                if (strcmp(queries[i], stringList[j])==0){
                count++;
                }  }
            result[i] = count;
        }
   return result; 
}

int main(){
    char stringList[1000][100];
    char query[1000][100];
    int stringlist_count, query_count;
    int result_count;

    scanf("%d", &stringlist_count);
    for(int i =0; i<stringlist_count;i++){
        scanf("%99s", stringList[i]);
    }

    scanf("%d", &query_count);
    for(int i =0; i<query_count;i++){
        scanf("%99s", query[i]);
    }

    int* result_arr = matchingStrings(stringlist_count,stringList,query_count,query,&result_count);

    for(int i = 0; i < result_count; i++){
    printf("\n%d", result_arr[i]);
    }
    return 0;
}
