#include <stdio.h>

struct user{
    int id;
    char name[50];
    int age;  };

void create(){         // create user records 
    struct user u1;
    printf("Enter ID: ");     // taking inputs from the user
    scanf("%d", &u1.id);
    printf("Enter Name: ");
    scanf("%s", u1.name);
    printf("Enter Age: ");
    scanf("%d", &u1.age);

     FILE *fp;
    fp = fopen("users.txt","a");      

    if(fp == NULL){
    printf(" File can't be opened \n");
    return;
    }
    else {
    fprintf(fp,"\n %d\t %s\t %d", u1.id, u1.name, u1.age);    // it will be appended/created at the end of the file...as mode-a
    }
    fclose(fp);
    printf("\n user created successfully\n ");  }


 void read(){       // read all the user records in the file 
    FILE *fp;
    fp = fopen("users.txt", "r");
    if (fp ==NULL){
        printf(" File can't be opened. ");
        return;
    }
    struct user u1;
    while((fscanf(fp,"%d %s %d", &u1.id, u1.name, &u1.age))==3)  // while the fscanf read 3 values in the file, 3 values will be displayed untilthe EOF
      {
        printf("\n %-10d\t %-15s\t %d", u1.id, u1.name, u1.age); }   // 3 values printed on the screen, %-10d & %-15s gives min of 10 & 15 size column to the id and name

    fclose(fp);
    printf("\n user read successfully\n ");  }

 void update() {     // updates the user records by asking the id & choice of what to update
    struct user u1;
    int newid, choice;
    int found = 0;      // used to determine if the id entered by the user is there in the file or not

    printf("Enter id to update: ");
    scanf("%d", &newid);

    printf(" 1.) Update Name");
    printf("\n2.) Update Age");
    printf("\n3.) Update Both");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    FILE *fp = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
         printf("File can't be opened.\n");   
         if (fp) fclose(fp);  if(temp) fclose(temp);  // if fp not null ie opened-> close it, if temp opened-> close it
         return; }

    while (fscanf(fp, "%d %s %d", &u1.id, u1.name, &u1.age) == 3)  {
        if (newid == u1.id)  {
            found = 1;

            if (choice == 1)  {
                printf("Enter new name: ");
                scanf("%s", u1.name);
            }
            else if (choice == 2)  {
                printf("Enter new age: ");
                scanf("%d", &u1.age);
            }
            else if (choice == 3) {
                printf("Enter new name: ");
                scanf("%s", u1.name);
                printf("Enter new age: ");
                scanf("%d", &u1.age);
            }
            else  { printf("Invalid choice.\n"); }
        }
        fprintf(temp, "%d\t%s\t%d\n", u1.id, u1.name, u1.age);
    }

    fclose(fp); fclose(temp);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found) printf("\nUser updated successfully.\n");
    else   printf("\nUser ID not found.\n");    }


 void delete(){           // deletes the user records in the file
    struct user u1; 
    int newid; int found=0;
    printf(" Enter the id to be deleted: ");
    scanf("%d",&newid);

    FILE *fp = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
   
    if (fp == NULL || temp == NULL) {
         printf("File can't be opened.\n");   
         if (fp) fclose(fp);  if(temp) fclose(temp);  
         return; }

     while (fscanf(fp, "%d %s %d", &u1.id, u1.name, &u1.age) == 3)  {
        if (newid == u1.id)  {
            found = 1;
            continue;}      // ie the id matched, will not be included in the temp file

        fprintf(temp, "%d\t%s\t%d\n", u1.id, u1.name, u1.age); }
        fclose(fp); fclose(temp);

        remove("users.txt");
        rename("temp.txt","users.txt");

        if (found) printf("\ndeleted successfully\n");
        else  printf("\n id not found\n");    }
        

int main(){
   
    printf("\n USER MANAGEMENT SYSYTEM :-\n ");
    printf("\n 1.) Create User ");
    printf("\n 2.) Read User ");
    printf("\n 3.) Update User ");
    printf("\n 4.) Delete User ");
    printf("\n 5.) Exit\n");
    int choice;
    do {        // do while loop so that user can repeatedly do CRUD opreations
    printf("\n Enter your choice : ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
        create();
        break;

        case 2:
        read();
        break;
        
        case 3:
        update();
        break;

        case 4:
        delete();
        break;

        case 5:
        printf("\n Exited from the system ");
        break;

        default:
        printf("\n Invalid Choice ");
        break;
    } }
    while ( choice !=5);  
    return 0;  }