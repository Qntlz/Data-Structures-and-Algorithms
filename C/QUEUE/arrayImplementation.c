#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Basic Array Implementation of Queue (Circular Array Method)
// Queue: "FIRST in, FIRST Out"

#define MAX 5

typedef struct {
    int front, rear;
    int arr[MAX];
} Queuetype, *Queue;

void initQueue(Queue*);
void enqueue(Queue*, int);
void dequeue(Queue*);
bool isEmpty(Queue);
bool isFull(Queue);
void display(Queue);

int main() {
    Queue L;

    // Initialize Queue
    initQueue(&L);

    printf("Enqueue: \n\n");
    for (int i = 0; i < MAX; i++) {
        enqueue(&L, i + 1);
    }

    display(L);  // Pass the Queue, not the address of the pointer

    // Dequeue test
    printf("Dequeue:\n\n");
    display(L);
    while (!isEmpty(L)) {  // Pass the Queue, not the address of the pointer
        dequeue(&L);
        display(L);
    }

    return 0;
}   

void initQueue(Queue *L) {
    *L = malloc(sizeof(Queuetype));
    if (*L != NULL) {
        (*L)->front = -1;
        (*L)->rear = -1;
    }
}

bool isEmpty(Queue L) {
    return (L->front == -1);
}

bool isFull(Queue L) {
    return ((L->rear + 1) % MAX == L->front);
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

void dequeue(Queue *L) {
    if (isEmpty(*L)) {
        printf("Queue is EMPTY\n");
    } else {
        // If only one element was in the queue, reset it
        if ((*L)->front == (*L)->rear) {
            (*L)->front = (*L)->rear = -1;
        } else {
            (*L)->front = ((*L)->front + 1) % MAX;
        }
    }
}

void display(Queue L) {
    if (isEmpty(L)) {
        printf("Queue is EMPTY\n");
    } else {
        printf("Queue: ");
        int i = L->front;
        while (i != L->rear) {
            printf("%d ", L->arr[i]);
            i = (i + 1) % MAX;
        }
        // Print the rear element
        printf("%d ", L->arr[L->rear]);
        printf("\nFront: %d Rear: %d\n\n", L->arr[L->front], L->arr[L->rear]);
    }
}
