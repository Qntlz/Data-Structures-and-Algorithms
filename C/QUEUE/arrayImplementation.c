#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Basic Array Implementation of Queue (Circular Array Method)
// Queue: "FIRST in, FIRST Out"

#define MAX 5
#define rogueVal -999

typedef struct {
    int front, rear;
    int arr[MAX];
} Queuetype, *Queue;

void initQueue(Queue*);
void enqueue(Queue*, int);
int dequeue(Queue*);
void display(Queue*);   // Display function
bool isEmpty(Queue);
bool isFull(Queue);

int main() {
    Queue L;

    // Initialize Queue
    initQueue(&L);

    // Enqueue
    for (int i = 0; i < MAX; i++) {
        enqueue(&L, i + 1);
    }

    // Display the Queue (mimic dequeue-enqueue)
    printf("\nDisplay Queue:\n");
    display(&L);

    //Dequeue
    printf("Dequeue:\n");
    while (!isEmpty(L)){
        printf("%d\n",dequeue(&L));
    }
    
    if(isEmpty(L)) printf("Queue is EMPTY");

    return 0;
}

void initQueue(Queue *L) {
    *L = malloc(sizeof(Queuetype));
    if (*L != NULL) {
        (*L)->front = (*L)->rear = -1;
    }
}

bool isEmpty(Queue L) {
    return (L->front == -1);
}

bool isFull(Queue L) {
    return ((L->rear + 2) % MAX == L->front);
}

void enqueue(Queue *L, int num) {
    if (isFull(*L)) {
        printf("Queue is FULL!\n");
    } else {
        if (isEmpty(*L)) {
            // If the queue is empty, set front & rear to index 0
            (*L)->front = (*L)->rear = 0;
        } else {
            // Circular increment of rear
            (*L)->rear = ((*L)->rear + 1) % MAX;
        }
        (*L)->arr[(*L)->rear] = num;
    }
}

int dequeue(Queue *L) {
    if (isEmpty(*L)) {
        printf("Queue is EMPTY\n");
        return rogueVal;
    } else {
        int hold;
        // If only one element was in the queue, reset it
        if ((*L)->front == (*L)->rear) {
            hold = (*L)->arr[(*L)->front];
            (*L)->front = (*L)->rear = -1;
        } else {
            hold = (*L)->arr[(*L)->front];
            (*L)->front = ((*L)->front + 1) % MAX;
        }
        return hold;
    }
}

void display(Queue *L) {
    if (isEmpty(*L)) {
        printf("Queue is EMPTY\n");
        return;
    }

    int originalFront = (*L)->front;   // Mark the original front position
    int currentPos = (*L)->front;      // Start from the front

    do {
        printf("%d\n", (*L)->arr[currentPos]);  // Print the current element

        // Simulate dequeue by moving the front to the next position
        currentPos = (currentPos + 1) % MAX;    // Circular increment of position

        // Simulate enqueue by considering the currentPos element at the rear
    } while (currentPos != originalFront);  // Stop once we cycle back to the original front
}
