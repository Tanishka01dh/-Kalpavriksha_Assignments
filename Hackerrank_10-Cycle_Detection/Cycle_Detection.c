#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct SinglyLinkedListNode {
    int data;
    struct SinglyLinkedListNode* next;
} SinglyLinkedListNode;

SinglyLinkedListNode* createNode(int data){    
    SinglyLinkedListNode* newnode = malloc(sizeof(SinglyLinkedListNode));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void insertNode(SinglyLinkedListNode** head, SinglyLinkedListNode** tail, int data){    // Function inserting a node at the end
    
    SinglyLinkedListNode* newnode = createNode(data);
    if(*head == NULL){
        *head = newnode;
        *tail = newnode;
    }
    else{
        (*tail)->next = newnode;
        *tail = newnode;
    }
}

bool has_cycle(SinglyLinkedListNode* head) {  // Function to detect a cycle
    SinglyLinkedListNode* slow = head;
    SinglyLinkedListNode* fast = head;

    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
            return 1;
    }
    return 0;
}

int main() {
    int tests;
    scanf("%d", &tests);    // no of test cases

    for(int t = 0; t < tests; t++){
        int index, num_0f_nodes;

        scanf("%d", &index);      // cycle index(-1 for no cycle)
        scanf("%d", &num_0f_nodes);      // total nodes in list

        SinglyLinkedListNode* head = NULL;
        SinglyLinkedListNode* tail = NULL;
        SinglyLinkedListNode* target = NULL;

        for(int i = 0; i < num_0f_nodes; i++){    //creating linkedlist 
            int data;
            scanf("%d", &data);

            insertNode(&head, &tail, data);
            if(i == index){
                target = tail; }
        }
        if(index >= 0 && target != NULL){       // creating cycle
            tail->next = target;
        }

        int result = has_cycle(head);
        printf("%d", result);

        if(tail != NULL){           //  breaking cycle &freeing memory
            tail->next = NULL;
        }
        SinglyLinkedListNode* temp = head;    
        while(temp != NULL){
            SinglyLinkedListNode* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    return 0;
}

