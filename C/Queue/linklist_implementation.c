#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Basic Linked List Implementation of Queue
// Queue: "FIRST in, FIRST Out"

#define rogueVal -999

typedef struct node
{
    int data;
    struct node *next;
} Node, *List;

typedef struct
{
    List front;
    List rear;
} QueueType, *Queue;

void initList(Queue *);
void enqueue(Queue*, int);
int dequeue(Queue*);
bool empty(Queue);
void display(Queue*);

int main()
{
    Queue L;

    // Initialize List
    initList(&L);

    // Enqueue
    for (int i = 0; i < 5; i++){
        enqueue(&L, i + 1);
    }

    printf("Elements in Queue:\n");
    display(&L);


    printf("Dequeue: \n");
    while (!empty(L)){
        printf("%d\n",dequeue(&L));
    }

    if(empty(L)) printf("Queue is EMPTY!\n");
   
    return 0;
}

void initQueue(Queue *L)
{
    *L = malloc(sizeof(QueueType));

    if(*L != NULL){
        (*L)->front = (*L)->rear = NULL;
    }
}

bool empty(Queue L)
{
    return L->front == NULL;
}

void enqueue(Queue *L, int num){                // Insert
    List newNode = malloc(sizeof(Node));
    if (newNode != NULL){
        newNode->data = num;
        newNode->next = NULL;
    }

    if (empty(*L)){   // If the list is empty
        (*L)->front = newNode;
    }
    else{
        (*L)->rear->next = newNode;
    }
    (*L)->rear = newNode;                          // Point rear to the new node
}
int dequeue(Queue *L)
{ // Delete
    if (empty(*L)){
        printf("Queue is EMPTY!\n");
        return rogueVal;
    }
    else{
        List temp = (*L)->front;
        int hold = temp->data;
        (*L)->front = temp->next;
        if ((*L)->front == NULL){ // If list has one element
            (*L)->rear = NULL;
        }
        free(temp);
        return hold; 
    }
}

void display(Queue *L) {
    if (empty(*L)) {
        printf("Queue is empty.\n");
        return;
    }

    List mark = (*L)->front;  // Mark the original front
    do {
        // Simulate dequeue by moving the front pointer but don't free the memory
        int hold = (*L)->front->data;
        printf("%d\n", hold);

        // Move the front to the next node (simulating dequeue)
        (*L)->rear->next = (*L)->front;  // Connect the front to the rear
        (*L)->front = (*L)->front->next; // Update the front to the next element
        (*L)->rear = (*L)->rear->next;   // Move the rear to point to the old front
        (*L)->rear->next = NULL;         // Ensure the new rear's next is NULL

    } while ((*L)->front != mark); // Stop once we reach the original front
}



