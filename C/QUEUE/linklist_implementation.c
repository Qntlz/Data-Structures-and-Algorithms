#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Basic Linked List Implementation of Queue
// Queue: "FIRST in, FIRST Out"

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
void enqueue(Queue, int);
void dequeue(Queue);
bool empty(Queue);
void display(Queue);

int main()
{
    Queue L;

    // Initialize List
    initList(&L);

    // Enqueue
    printf("Enqueue: \n\n");
    for (int i = 0; i < 5; i++){
        enqueue(L, i + 1);
        display(L);
    }

    // Dequeue
    printf("Dequeue: \n\n");
    do{
        display(L);
        dequeue(L);
    } while (!empty(L));

    if(empty(L)){
        printf("Queue is Empty!");
    }

    return 0;
}

void initList(Queue *L)
{
    *L = malloc(sizeof(QueueType));

    if(*L != NULL){
        (*L)->front = NULL;
        (*L)->rear = NULL;
    }
}

bool empty(Queue L)
{
    return L->front == NULL;
}

void enqueue(Queue L, int num){                // Insert
    List newNode = malloc(sizeof(Node));
    if (newNode != NULL){
        newNode->data = num;
        newNode->next = NULL;
    }

    if (empty(L)){   // If the list is empty
        L->front = newNode;
    }
    else{
        L->rear->next = newNode;
    }
    L->rear = newNode;                          // Point rear to the new node
}
void dequeue(Queue L)
{ // Delete
    if (!empty(L))
    {
        List temp = L->front;
        L->front = temp->next;
        if (L->front == NULL){ // If list has one element
            L->rear = NULL;
        }
        free(temp);
    }
}

void display(Queue L)
{
    List trav;
    printf("Queue: ");
    for (trav = L->front; trav != NULL; trav = trav->next) {
        printf("%d ", trav->data);
    }
    printf("\nFront: %d Rear: %d\n\n", L->front->data, L->rear->data);
}


