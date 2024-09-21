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

typedef int List;

void initList(List*);
void initVH(VirtualHeap*);
int allocSpace(VirtualHeap*);
void deAllocSpace(VirtualHeap*,int);
bool isEmpty(List);
bool isFull(VirtualHeap);
void push(List*,VirtualHeap*,int);
int pop(List *L,VirtualHeap *VH);
int peek(List,VirtualHeap);


int main(){

    List top;
    VirtualHeap myHeap;

    initList(&top);
    initVH(&myHeap);

    push(&top,&myHeap,1);
    push(&top,&myHeap,2);
    push(&top,&myHeap,3);

    printf("Top: %d\n\n",peek(top,myHeap));

    for (int i = 0; i < 3; i++){
        printf("Pop: %d\n",pop(&top,&myHeap));
        printf("Top: %d\n\n",peek(top,myHeap));
    }

    return 0;
}

void initList(List *top){
    *top = -1;
}
void initVH(VirtualHeap *VH){
    VH->avail = 0;
    for (int i = 0; i < MAX - 1; i++){
        VH->Nodes[i].link = i + 1;
    }
    VH->Nodes[MAX - 1].link = -1;
    
}
int allocSpace(VirtualHeap *VH){
    List space = VH->avail;
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

bool isEmpty(List top){
    return top == -1;
}
bool isFull(VirtualHeap VH){
    return VH.avail == -1;
}

void push(List *top,VirtualHeap *VH,int num){
    // Check if full
    if(isFull(*VH)) printf("Stack is FULL\n");
    else{
        List space = allocSpace(VH);
        if(space != -1){
            VH->Nodes[space].data = num;          // Store the value
            VH->Nodes[space].link = *top;         // Link the new element to the previous top
            *top = space;                         // Update the top of the stack
        }               
    }
}

int pop(List *top,VirtualHeap *VH){
    // Check if empty
    if(isEmpty(*top)) {
        printf("Stack is EMPTY\n");
    }
    else{
        List temp = *top;                           // Store current top
        List hold = VH->Nodes[temp].data;           // Store the value at top
        *top = VH->Nodes[temp].link;                // Update top
        deAllocSpace(VH,temp);
        return hold;
    }
    return roqueVal;                              // Return Sentinel Value
}

int peek(List L, VirtualHeap VH) {
    if (isEmpty(L)) {
        printf("Stack is EMPTY\n");
        return roqueVal;
    } else {
        return VH.Nodes[L].data;
    }
}



