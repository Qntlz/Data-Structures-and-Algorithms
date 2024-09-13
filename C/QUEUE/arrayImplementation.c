#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Basic Array Implementation of Queue (Circular Array Method)
// Queue: "FIRST in, FIRST Out"

#define MAX 5

typedef struct {
    int front, rear;
    int arr[MAX];
} Queue;

void initQueue(Queue*);
void enqueue(Queue*, int);
void dequeue(Queue*);
bool isEmpty(Queue*);
bool isFull(Queue*);
void display(Queue*);

int main()
{
    Queue L;

    // Initialize Queue
    initQueue(&L);

    printf("Enqueue: \n\n");
    for (int i = 0; i < 5; i++) {
        enqueue(&L, i + 1);
    }

    display(&L);

    // Dequeue test
    printf("Dequeue:\n\n");
    display(&L);
    while (!isEmpty(&L)){
        dequeue(&L);
        display(&L);
    }

    return 0;
}

void initQueue(Queue *L) {
    L->front = -1;
    L->rear = -1;
}

bool isEmpty(Queue *L) {
    return (L->front == -1);
}

bool isFull(Queue *L) {
    return (L->rear + 1) % MAX == L->front;
}

void enqueue(Queue *L, int num) {
    if (isFull(L)) {
        printf("Queue is FULL!\n");
    } else {
        // If the queue is empty, set front & rear to index 0
        if (isEmpty(L)) {
            L->front = L->rear = 0;
        } else {
            // Circular increment of rear
            L->rear = (L->rear + 1) % MAX;
        }
        L->arr[L->rear] = num;
    }
}

void dequeue(Queue *L) {
    if (isEmpty(L)) {
        printf("Queue is EMPTY\n");
    } else {
        // Circular increment of front
        if (L->front == L->rear) { // Only one element was in the queue
            initQueue(L); // Reset the queue
        } else {
            L->front = (L->front + 1) % MAX;
        }
    }
}

void display(Queue *L) {
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
