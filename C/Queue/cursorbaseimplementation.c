#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Cursor-Base Implementation of Queue
// Queue: "FIRST In, FIRST Out"

#define MAX 3
#define roqueVal -999

typedef struct
{
    int data, link;
} Cell;

typedef struct
{
    Cell Nodes[MAX];
    int avail;
} VirtualHeap;

typedef struct
{
    int front, rear;
} Queuetype, *Queue;

void initQueue(Queue *);
void initVH(VirtualHeap *);
int allocSpace(VirtualHeap *);
void deAllocSpace(VirtualHeap *, int);
bool isEmpty(Queue);
bool isFull(VirtualHeap);
void enqueue(Queue *, VirtualHeap *, int);
int dequeue(Queue *, VirtualHeap *);
void printFront(Queue, VirtualHeap);
void printRear(Queue, VirtualHeap);

int main()
{

    Queue Q;
    VirtualHeap myHeap;

    // Initialize
    initQueue(&Q);
    initVH(&myHeap);

    // Enqueue
    enqueue(&Q, &myHeap, 1);
    enqueue(&Q, &myHeap, 2);
    enqueue(&Q, &myHeap, 3);
    //enqueue(&Q, &myHeap, 4);                          // Test case to check if queue is full


    // Dequeue
    for (int i = 0; i < 4; i++){
        printFront(Q, myHeap);
        printRear(Q, myHeap);
        printf("Dequeue: %d\n\n", dequeue(&Q, &myHeap));
    }

    return 0;
}

void initQueue(Queue *Q)
{
    *Q = malloc(sizeof(Queuetype));

    if (*Q != NULL){
        (*Q)->front = (*Q)->rear = -1;
    }
}
void initVH(VirtualHeap *VH)
{
    VH->avail = 0;
    for (int i = 0; i < MAX - 1; i++){
        VH->Nodes[i].link = i + 1;
    }
    VH->Nodes[MAX - 1].link = -1;
}
int allocSpace(VirtualHeap *VH)
{
    int space = VH->avail;
    if (space != -1){
        VH->avail = VH->Nodes[space].link;
    }
    return space;
}
void deAllocSpace(VirtualHeap *VH, int index)
{
    // Check index if within bounds
    if (index >= 0 && index < MAX){
        VH->Nodes[index].link = VH->avail;
        VH->avail = index;
    }
}
bool isEmpty(Queue Q)
{
    return Q->front == -1;
}
bool isFull(VirtualHeap VH)
{
    return VH.avail == -1;
}

void enqueue(Queue *Q, VirtualHeap *VH, int elem){
    if(isFull(*VH)){
        printf("Queue is FULL!\n");
    } else {
        int space = allocSpace(VH);
        if (space != -1){
            VH->Nodes[space].data = elem;
            VH->Nodes[space].link = -1;                 // New rear has no next element
            if (isEmpty(*Q)){
                (*Q)->front = space;                    // Set space to front for first element
            } else {
                VH->Nodes[(*Q)->rear].link = space;     // Link the old rear to new rear
            }
            (*Q)->rear = space;                         // Update rear to the new space
        }
    }
}

int dequeue(Queue *Q, VirtualHeap *VH){
    if(isEmpty(*Q)){
        printf("Queue is EMPTY!\n");
        return roqueVal;
    } else {
        int temp = (*Q)->front;
        int hold = VH->Nodes[temp].data;

        // Only one element
        if((*Q)->front == (*Q)->rear){
            (*Q)->front = (*Q)->rear = -1;              // Reset queue if only one element
        } else {
            (*Q)->front = VH->Nodes[temp].link;         // Move front to the next element
        }
        deAllocSpace(VH, temp);
        return hold;
    }
}


void printFront(Queue Q, VirtualHeap VH)
{
    if(!isEmpty(Q)) printf("Front: %d\n", VH.Nodes[Q->front].data);
}
void printRear(Queue Q, VirtualHeap VH)
{
    if(!isEmpty(Q)) printf("Rear: %d\n", VH.Nodes[Q->rear].data);
}