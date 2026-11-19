#include <stdio.h>
#include <stdlib.h>

typedef struct SinglyLinkedListNode {
    int data;
    struct SinglyLinkedListNode* next;
} SinglyLinkedListNode;

SinglyLinkedListNode* createNode(int data) {    
    SinglyLinkedListNode* newnode = malloc(sizeof(SinglyLinkedListNode));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

SinglyLinkedListNode* insertNode(SinglyLinkedListNode *head, int value) {   //inserting node at the end
    SinglyLinkedListNode* newNode = createNode(value);
    if(head == NULL){
        head = newNode;
        return head;
    }
    SinglyLinkedListNode *temp = head;

    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    
    SinglyLinkedListNode extra;
    extra.next = NULL;
    SinglyLinkedListNode* tail = &extra;

    while(head1 != NULL && head2 != NULL){
        if(head1->data <= head2->data){
            tail->next = head1;
            head1 = head1->next;
        }
        else{
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
    }
    if(head1 != NULL)  tail->next = head1;
    else tail->next = head2;

    return extra.next;
}

void display(SinglyLinkedListNode *head){    //displaying the list
    SinglyLinkedListNode *temp = head;

    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\t");
}

int main(){
    int test, num_of_nodes_lis1,num_of_nodes_lis2, value;

    scanf("%d", &test);   // no of test cases

    for(int t=0;t<test;t++){
   
        SinglyLinkedListNode *head1 = NULL;
        SinglyLinkedListNode *head2 = NULL;
        SinglyLinkedListNode *mergedHead = NULL;

        scanf("%d", &num_of_nodes_lis1);    // num of nodes in linkedlist 1
        for(int i = 0; i < num_of_nodes_lis1; i++){
            scanf("%d", &value);
            head1 = insertNode(head1, value);
        }

        scanf("%d", &num_of_nodes_lis2);    // num of nodes in linkedlist 2
        for(int i = 0; i < num_of_nodes_lis2; i++){
            scanf("%d", &value);
            head2 = insertNode(head2, value);
        }
        
        mergedHead = mergeLists(head1, head2); 
        display(mergedHead);

        SinglyLinkedListNode *temp;   // freeing memory
        while(mergedHead != NULL){
            temp = mergedHead;
            mergedHead = mergedHead->next;
            free(temp);
        }
    }
    return 0;
}

