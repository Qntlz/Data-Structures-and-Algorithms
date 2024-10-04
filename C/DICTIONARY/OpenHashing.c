#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Dictionary (Open-Hashing)

#define MAX 10
#define EMPTY 0
#define DELETE -1


typedef struct node {
    int data;
    struct node *next;
} Node, *NodePtr;

typedef Node Dictionary;

void initDictionary(Dictionary*);
void insert(Dictionary* , int);
void delete(Dictionary* , int);
bool search(Dictionary* , int);
void display(Dictionary*);
int hash(int key);

int main() {
    Dictionary A[MAX]; // Declare the dictionary
    int keys[] = {50,21,58,17,15,49,56,22,23,25};

    initDictionary(A); // Initialize the dictionary

    for (int i = 0; i < MAX; i++){
        insert(A,keys[i]);
    }

    delete(A,15);
    
    display(A);
    
    (search(A,17)) ? printf("Element 17 is Present\n") : printf("Element 17 is Missing\n");

    return 0;
}

// Function to initialize the dictionary
void initDictionary(Dictionary *A) {
    for (int i = 0; i < MAX; i++){
        A[i].data = EMPTY;
        A[i].next = NULL;
    }
}

// Hash Function
int hash(int key) {
    return key % 10; 
}

void insert(Dictionary *A, int key){

    int index = hash(key);
    if(A[index].data == EMPTY){
        A[index].data = key;
    }
    else{
        // Collision: Insert into the linked list at the end
        NodePtr newNode = malloc(sizeof(Node));
        if(newNode != NULL){
            newNode->data = key;
            newNode->next = NULL;
        }
        NodePtr temp = &A[index];
        while (temp->next != NULL) {
                temp = temp->next; // Traverse to the end of the list
            }
        temp->next = newNode; // Add new node at the end
    }
}

void delete(Dictionary *A , int key) {
    int index = hash(key);

    // Check if the key is in the head node (A[index])
    if (A[index].data == key) {
        if (A[index].next == NULL) {
            A[index].data = EMPTY; // No chain, simple deletion
        } else {
            // If there is a chain, move the data from the next node up and adjust pointers
            NodePtr temp = A[index].next;
            A[index].data = temp->data;  // Move the next node's data to the head
            A[index].next = temp->next;  // Update head's next pointer
            free(temp);  // Free the old head of the chain
        }
    }
    // Now check the rest of the chain
    else {
        NodePtr *trav;
        for (trav = &(A[index].next); *trav != NULL && (*trav)->data != key; trav = &(*trav)->next) {}

        if (*trav != NULL) {  // Found the key in the chain
            NodePtr temp = *trav;
            *trav = temp->next;  // Adjust the pointers to bypass the node
            free(temp);  // Free the node
        }
    }
}


bool search(Dictionary *A , int key){
    int index = hash(key);
    return (A[index].data == key);
}

void display(Dictionary *A) {
    for (int i = 0; i < MAX; i++) {
        NodePtr trav = &A[i];
       
            while (trav != NULL) {
                printf("%d ", trav->data);
                trav = trav->next;
            }
        
        printf("\n");
    }
}



