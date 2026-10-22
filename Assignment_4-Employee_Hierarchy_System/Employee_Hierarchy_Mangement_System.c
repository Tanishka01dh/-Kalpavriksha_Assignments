#include<stdio.h>
struct Employee{
    int id;
    char name[50];
    char designation[30];
    struct Employee* manager;
    struct Employee* reports[50];
    int reportCount;
    int active;  };

struct Employee TotalEmployees[100];  //structure array that stores all employees
int ActiveEmployeeCount = 0;

int FindEmployee(int id){         // checks if the employee exists or not in the Employees array
    for (int i=0; i<100 ; i++){
        if (TotalEmployees[i].active == 1 && TotalEmployees[i].id == id)  
        return i;
    }
  return -1;
}

int findFreeSlot(){       // returns freeslots that are either unused or inactive
    for (int i = 0; i < 100; i++) {
        if (TotalEmployees[i].active == 0)
            return i;
    }
    return -1;
}

void AddEmployee(){     // adds employee in the memory
    
    int managerID;
    int managerIndex;
    int index = findFreeSlot();
    if (index == -1) {
        printf("\nNo free employee slots available.\n");
        return; }
    
    printf("\nEnter Id: ");
    scanf("%d", &TotalEmployees[index].id );

    if (FindEmployee(TotalEmployees[index].id) != -1) {
        printf("\nEmployee ID already exists.\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", TotalEmployees[index].name);
    printf("Enter Designation: ");
    scanf(" %29[^\n]", TotalEmployees[index].designation);

    TotalEmployees[index].manager = NULL;
    TotalEmployees[index].reportCount = 0;
    for (int i = 0; i < 50; i++) {
    TotalEmployees[index].reports[i] = NULL;
    }

    if(ActiveEmployeeCount ==0){
        TotalEmployees[index].active = 1;
        ActiveEmployeeCount++;
        printf("\nFirst employee is the CEO");
    }
    else {
        printf(" Enter manager id: ");
        scanf("%d", &managerID);
        if (FindEmployee(managerID)== -1){
            printf("\nNo such manager exists");
            return;  }
        
        managerIndex = FindEmployee(managerID);
        TotalEmployees[index].manager = &(TotalEmployees[managerIndex]);   //the address of the employee struct at managerIndex stored in manager pointer 
        
        TotalEmployees[managerIndex].reports[TotalEmployees[managerIndex].reportCount] = &(TotalEmployees[index]);   // address of employee struct at index, stored in the reports of manager index 
        TotalEmployees[managerIndex].reportCount++;

        TotalEmployees[index].active = 1;
        ActiveEmployeeCount++;
        
        printf("\nEmployee added\n");
    } } 


void RemoveEmployee(){     // removing the employee
    int id, index;

    printf("\n Enter the id to be removed: ");
    scanf("%d", &id);

    index = FindEmployee(id);
    if( index == -1){
        printf("\n Id not found "); 
        return ; }
    
    struct Employee *emp = &TotalEmployees[index];
    struct Employee *mgr = emp-> manager;

    if (mgr == NULL) {
        printf("\nCEO can't be removed");
        return;  }
    
    struct Employee *target = mgr;         // finding target sibling to transfer reports
    int min = 100;
    for (int i = 0; i < mgr -> reportCount; i++) {
        struct Employee *sibling = mgr -> reports[i];
        if (sibling != emp && sibling -> reportCount < min) {
            min = sibling -> reportCount;
            target = sibling;
        }  }

    if (target->reportCount + emp->reportCount > 50) {
        printf("\nCannot transfer reports: capacity exceeded");
        return; }

    for (int i = 0; i < emp->reportCount; i++) {     // transferring direct reports to target
    struct Employee *reportingEmp = emp->reports[i];

    reportingEmp -> manager = target;
    target-> reports[target-> reportCount++] = reportingEmp; }
    emp->reportCount = 0;

    for (int i = 0; i < mgr->reportCount; i++) {    // Removing employee from manager's reports
        if (mgr->reports[i] == emp) {
            for (int j = i; j < mgr->reportCount - 1; j++)
                mgr->reports[j] = mgr->reports[j + 1];

            mgr->reportCount--;
            break;
        }  }

    emp -> active = 0;
    printf("\n Employee removed");
    }

void DisplayBranch(struct Employee *emp, int level){        // recursive function for hierarchy printing
    
    for ( int i = 0; i < level; i++)
        printf("    ");

    printf(" %d  %s  (%s)\n", emp->id, emp->name, emp->designation);

    for (int i = 0; i < emp->reportCount; i++)
        DisplayBranch(emp->reports[i], level + 1);    
    }

void DisplayEmployeeHierarchy(){     // for displaying indivisual employee hierarchy
    int id,index;

    printf("\nEnter id to be displayed hierarchially: ");
    scanf("%d", &id);
    index = FindEmployee(id);

    if (index == -1) {
        printf("\nEmployee not found");
        return;   }
    
    DisplayBranch(&TotalEmployees[index], 0);   
    }

void DisplayTotalHierarchy(){      // for displaying total hierarchy
    for (int i =0; i<100; i++){
        if ((TotalEmployees[i].active == 1) && (TotalEmployees[i].manager == NULL))
        DisplayBranch(&(TotalEmployees[i]),0);
    }
    return ;
}

int main(){
    int choice;
    printf("\n=== Employee Hierarchy Mnagaement System ===\n");
    printf("\n1. Add Employee\n");
    printf("2. Remove Employee\n");
    printf("3. Display Employee Hierarchy\n");
    printf("4. Display Complete Hierarchy\n");
    printf("5. Exit\n");
    do {
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

        switch (choice) {
    case 1:
    AddEmployee(); break;

    case 2:
        RemoveEmployee(); break;
        
    case 3:
        DisplayEmployeeHierarchy(); break;
        
    case 4:
        DisplayTotalHierarchy(); break;
        
    case 5:
        printf("\nExiting the System");
        break;

    default:{
        printf("\n Invalid choice");
        break;}
    } }
    while (choice != 5);
    return 0; }

