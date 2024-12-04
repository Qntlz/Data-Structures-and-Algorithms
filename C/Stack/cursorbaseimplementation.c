#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Cursor-Base Implementation of Stack
// Stack: "LAST In, FIRST Out"

#define MAX 10
#define roqueVal -999

typedef struct{
    int data,link;
}Cell;

typedef struct{
    Cell Nodes[MAX];
    int avail;
}VirtualHeap;

typedef struct{
    int top;
}Stacktype,*Stack;

void initStack(Stack*);
void initVH(VirtualHeap*);
int allocSpace(VirtualHeap*);
void deAllocSpace(VirtualHeap*,int);
bool isEmpty(Stack);
bool isFull(VirtualHeap);
void push(Stack*,VirtualHeap*,int);
int pop(Stack *,VirtualHeap *VH);
int peek(Stack,VirtualHeap);


int main(){

    Stack S;
    VirtualHeap myHeap;

    initStack(&S);
    initVH(&myHeap);

    push(&S,&myHeap,1);
    push(&S,&myHeap,2);
    push(&S,&myHeap,3);

    printf("Top: %d\n\n",peek(S,myHeap));

    for (int i = 0; i < 3; i++){
        printf("Pop: %d\n",pop(&S,&myHeap));
        printf("Top: %d\n\n",peek(S,myHeap));
    }

    return 0;
}

void initStack(Stack *S){
    *S = malloc(sizeof(Stacktype));

    if(*S != NULL){
        (*S)->top = -1;
    }
}
void initVH(VirtualHeap *VH){
    VH->avail = 0;
    for (int i = 0; i < MAX - 1; i++){
        VH->Nodes[i].link = i + 1;
    }
    VH->Nodes[MAX - 1].link = -1;
    
}
int allocSpace(VirtualHeap *VH){
    int space = VH->avail;
    if(space != -1){
        VH->avail = VH->Nodes[space].link;
    }
    return space;
}
void deAllocSpace(VirtualHeap *VH,int index){
    // Check if index within bounds
    if(index >= 0 && index < MAX){
        VH->Nodes[index].link = VH->avail;
        VH->avail = index;
    }
}

bool isEmpty(Stack S){
    return S->top == -1;
}
bool isFull(VirtualHeap VH){
    return VH.avail == -1;
}

void push(Stack *S,VirtualHeap *VH,int num){
    // Check if full
    if(isFull(*VH)) printf("Stack is FULL\n");
    else{
        int space = allocSpace(VH);
        if(space != -1){
            VH->Nodes[space].data = num;          // Store the value
            VH->Nodes[space].link = (*S)->top;         // Link the new element to the previous top
            (*S)->top = space;                         // Update the top of the stack
        }               
    }
}

int pop(Stack *S,VirtualHeap *VH){
    // Check if empty
    if(isEmpty(*S)) {
        printf("Stack is EMPTY\n");
        return roqueVal;                              // Return Sentinel Value
    }
    else{
        int temp = (*S)->top;                           // Store current top
        int hold = VH->Nodes[temp].data;           // Store the value at top
        (*S)->top = VH->Nodes[temp].link;                // Update top
        deAllocSpace(VH,temp);
        return hold;
    }
}

int peek(Stack L, VirtualHeap VH) {
    if (isEmpty(L)) {
        printf("Stack is EMPTY\n");
        return roqueVal;
    } else {
        return VH.Nodes[L->top].data;
    }
}



