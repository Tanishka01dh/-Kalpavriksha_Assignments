#include<stdio.h>

struct student{
    int rollno;
    char name[50];
    float m1,m2,m3;
};

void rollnoList(struct student s1[100], int i, int n){
            if (i == n) return;
            printf("%d\t", s1[i].rollno);
            rollnoList( s1, i+1, n);
    }

int main(){
    int n;
    struct student s1[100];
    char grade;

    scanf("%d\n",&n);
    
    for(int i=0;i<n;i++){
    scanf("%d",&s1[i].rollno);
    scanf("%s",s1[i].name);
    scanf("%f",&s1[i].m1);
    scanf("%f",&s1[i].m2);
    scanf("%f",&s1[i].m3);  }
    
    for(int i=0;i<n;i++){
    printf("\nRoll: %d",s1[i].rollno);
    printf("\nName: %s",s1[i].name);

    float total = s1[i].m1 + s1[i].m2 + s1[i].m3;
    printf("\nTotal: %.2f", total);

    float avg = total/3;
    printf("\nAverage: %.2f",avg);

        if (avg >=85)        grade = 'A';
        else if (avg >= 70)  grade = 'B';
        else if (avg >= 50)  grade = 'C';
        else if (avg >= 35)  grade = 'D';
        else                 grade = 'F';
    printf("\nGrade: %c", grade);

        if (grade == 'A') printf("\nPerformance: *****\n");
        else if (grade == 'B') printf("\nPerformance: ****\n");
        else if (grade == 'C') printf("\nPerformance: ***\n");
        else if (grade == 'D') printf("\nPerformance: **\n");
        else  continue;    }
    
    printf("\nList of Roll Numbers: ");
    rollnoList(s1,0,n);
return 0;
}

