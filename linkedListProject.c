#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int data;
    struct NODE *next;
}Node;

//prototyping
void printList(Node *head);

void addAtEnd(Node *head, int value);

void deleteList(Node **head);

Node* search(Node *head, int value);

void insertNode(Node **head, int index, int value);
void deleteNode(Node **head, int key);

void printNode(Node *head, int index);

Node* reverse(Node *head);

Node* challenge1B(Node *head);

int main(int argc, char **argv){
    Node *head;
    Node *temp;
    

    head = (Node*)malloc(sizeof(Node));
    head->data = 5;
    head->next = NULL;

    temp = (Node*)malloc(sizeof(Node));
    temp->data = 10;
    head->next = temp;
    temp->next = NULL;   
    printList(head);
    printf("\n");
    printf("add 2, and 123123 to the end of the list\n");
    addAtEnd(head,2);
    addAtEnd(head,1232123);
    printList(head);
    printf("deleting node with value 5\n");
    deleteNode(&head,5);
    printList(head);
    printf("insert node at index 0 with value 1\n");
    
    insertNode(&head,0,1);
    printList(head);

    printf("search test\n");
    search(head,1232123);
    search(head,5);

    printf("print node value at index 3\n");
    printNode(head,3);
    
    addAtEnd(head, 4);
    addAtEnd(head,5);
    addAtEnd(head, 31);
    addAtEnd(head,14);

    printf("Before Reverse\n");
    printList(head);
    printf("Head Value: %d\n", head->data);
    printf("Head Next: %d\n", head->next->data);
    printf("Reverse Test\n");
    head = reverse(head);
    printList(head);
    printf("Head Value: %d\n", head->data); //did this to make sure head is in the right place
    printf("Head Next: %d\n", head->next->data);
    


    head = challenge1B(head);


    printf("\nDelete Test\n\n");
    printf("Before delete\n");
    printList(head);
    
    printf("After delete\n");
    deleteList(&head);


    printList(head);
    
    return 0;
}

void printList(Node *head){
    Node *current;
    current = head;
    printf("Data for List:\n");
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
        }

    printf("\n");
}

void addAtEnd(Node *head, int value){ //checked
    Node *endOfList;
    endOfList=head;
    while(endOfList->next != NULL){
        
        endOfList=endOfList->next;
        //printf("end of list: %d\n", endOfList->data);
    }
    Node *newNode = (Node*)malloc(sizeof(Node));
    endOfList->next=newNode;
    newNode->data=value;
    newNode->next=NULL;
}

void deleteList(Node **head){ //checked
    Node *headStart = *head; 
    Node *temp;


    //kill everything other than the head
    while (headStart != NULL) 
    {
       temp = headStart->next;
       //printf("Deleting Value:%d\n",temp->data);
       free(headStart);
       headStart=temp;
    }
    //kill the head
    *head = NULL;
}



void insertNode(Node **head, int index, int value){ //checked
    int linkedListSize=0;
    Node* toGetSize=*head;
    while(toGetSize!=NULL){
        toGetSize = toGetSize->next;
        linkedListSize++;
    }
    
    


    //prep the new node to insert
    
    
    
    if(index < 0 || index > linkedListSize){ //if position is invalid
        printf("Invalid position to insert\n"); 
    } else if(index == 0){ //if position requires us to replace head
        struct NODE* newNode = (struct NODE*) malloc(sizeof(struct NODE)); 
        newNode->data = value;
        
        newNode->next = *head; //move the old head forward
        *head = newNode; //replace the head with prepped node
    }else {
        struct NODE* newNode = (struct NODE*) malloc(sizeof(struct NODE)); 
        newNode->data = value;
        newNode->next = NULL;
        
        // temp used to traverse the Linked List
        struct NODE* temp = *head; 
        
        // traverse till the nth node
       for(int i = 0; i < index; i++){
            temp = temp->next;
        }
    
        //attach node without compromising integrity of the list
        newNode->next= temp->next;
        temp->next = newNode;
    }
}



Node* search(Node *head, int data){ 
    if(head == NULL){
        return NULL;
    }
    Node *temp;

    temp = head;
    while(temp != NULL){ //while the end of the list is not reached
        if(temp->data == data){
            printf("Found node with value: %d\n", temp->data);
            return temp;
        }else{
            temp = temp->next;
        }
    }
    printf("Could not find node with value: %d\n", data);
    return NULL;
}

void deleteNode(Node **head, int key){ //checked
    Node *toDelete;
    Node *temp = *head;

    if (temp->data == key)
    {
        toDelete = *head;
        *head = toDelete->next;
        toDelete->next = NULL;
        free(toDelete);
        //return *head;
    }
    else
    {
        Node *current = *head;
        while (current->next != NULL)
        {
            if (current->next->data == key)
            {
                toDelete = current->next;
                current->next = current->next->next;
                free(toDelete);
                break;
            }
            else
                current = current->next;
        }
       //return *head;
    }
}


void printNode(Node *head, int index){//checked
    Node *temp;

    temp = head;
    for(int i = 0; i < index; i++){
        temp = temp->next;
    }
    printf("Value of Node: %d\n",temp->data);
}

Node* reverse(Node *head){
    Node* curr = head;
    Node* prev = NULL;
    Node* traverse = NULL;
    while(curr != NULL){
    	traverse = curr->next;
    	curr->next = prev;
    	prev = curr;
    	curr = traverse;
    }
    curr = prev;

    return curr;

}

Node* challenge1B(Node *head){ //this function, 
    printf("\nChallenge 1b\n");

    Node* tortoise = head;
    Node* hare = head;
    while(hare->next->next!=NULL){
        hare = hare->next->next;
        tortoise = tortoise->next;
    }

    printf("Before reverse right side\n");
    printList(head);
    printf("After reverse right side\n");
    hare = tortoise->next;
    tortoise->next = reverse(hare);

    printList(head);
    
    //now we merge the left and right
    //How do?
    printf("Beginning merge\n");
    Node* curr = head;
    Node* next = head->next;
    hare = tortoise->next;
    Node* carrot = hare->next;

    Node* saveForLater = hare;
    tortoise->next = NULL;
    while(next!=NULL){
        curr->next = hare;
        hare->next = next;
        curr = next;
        hare = carrot;
        next= next->next;
        carrot=carrot->next;
    }
    curr->next = hare;
    printf("After merge\n");
    printList(head);

    return head;

}