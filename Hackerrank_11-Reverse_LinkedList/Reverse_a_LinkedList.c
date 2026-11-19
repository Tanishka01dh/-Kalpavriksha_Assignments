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

SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {   //reversing the list
    SinglyLinkedListNode* prev = NULL;
    SinglyLinkedListNode* curr = llist;
    SinglyLinkedListNode* next = NULL;
    while( curr != NULL){
       next = curr->next;
       curr->next = prev;
       prev = curr;
       curr = next;
    }
 return prev;
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
    int test, num_of_nodes, value;

    scanf("%d", &test);   // no of test cases

    for(int t=0;t<test;t++){
   
        SinglyLinkedListNode *head = NULL;
        scanf("%d", &num_of_nodes);    // num of nodes in linkedlist

        for(int i = 0; i < num_of_nodes; i++){
            scanf("%d", &value);
            head = insertNode(head, value);
        }

        head = reverse(head);
        display(head);

        SinglyLinkedListNode *temp;   // freeing memory
        while(head != NULL){
            temp = head;
            head = head->next;
            free(temp);
        }
    }
    return 0;
}

