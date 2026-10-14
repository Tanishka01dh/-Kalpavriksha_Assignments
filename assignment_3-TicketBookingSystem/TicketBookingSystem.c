#include<stdio.h>
int main(){

    char name[50];
    int ticketNum;
    int choice;
    const int STANDARD = 150;
    const int PREMIUM =250;
    const int RECLINER = 400;
    int amount;
    float discount;
    float finalBill;
       
    printf("\n TICKET BOOKING SYSTEM \n");          // menue
    printf("Choice  category  Ticket price\n");
    printf("1       Standard   %d\n", STANDARD);
    printf("2       Premium    %d\n", PREMIUM);
    printf("3       Recliner   %d\n", RECLINER);

    printf("\nEnter name: ");
    scanf("%s", name);
    printf("Enter No. of tickets: ");
    scanf("%d", &ticketNum);

    if (ticketNum<1 || ticketNum>20) {                      // checking ticket number constraint
        printf(" Invalid Ticket count. It must be between 1 to 20\n");
        return 1; 
    }

    printf("Enter ticket category choice (1/2/3) : ");    
    scanf("%d",&choice);  
    
    printf("\nCustomer Name: %s", name);
    switch(choice){                               // category choice logic
        case 1:
        printf("\nTicket category: Standard");
        amount = ticketNum*STANDARD;
        break;
        case 2:
        printf("\nTicket category: Premium");
        amount = ticketNum*PREMIUM;
        break;
        case 3:
        printf("\nTicket category: Recliner");
        amount = ticketNum*RECLINER;
        break;
        default:
        printf("\nInvalid Ticket category choice");
        return 1;
    }
    printf("\nNo. of tickets: %d", ticketNum);  
    printf("\nSubtotal Amount: %d", amount);

    if (ticketNum >=5){                       // discount condition
        discount = 0.1*amount;
        printf("\nDiscount: %.2f", discount);}
    else{
        discount = 0;
        printf("\nDiscount: %.2f", discount);   
    }

    finalBill = amount - discount;
    printf("\nFinal Bill: %.2f", finalBill);       

    return 0;

}