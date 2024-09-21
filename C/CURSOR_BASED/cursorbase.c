#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Cursor-Based
    - Uses an array to simulate pointers, with an additional array that tracks 
    the availability of indices, mimicking the behavior of a free-list 
    (a list of available memory locations).

    Note: Feel free to have your own version. This code focuses on the
    basic concepts.
*/

#define MAX 10

typedef struct{
    int data, link;
}Cell;

typedef struct{
    Cell Nodes[MAX];
    int avail;
}VirtualHeap;

typedef int List;

void initList(List*);
void initVH(VirtualHeap*);
void display(List,VirtualHeap);
int allocSpace(VirtualHeap*);
void deAllocSpace(VirtualHeap*,int);
void insertFirst(List*,VirtualHeap*,int);
void insertLast(List*,VirtualHeap*,int);
void delElem(List*,VirtualHeap*,int);

int main(){

    List L;
    VirtualHeap myHeap;

    initList(&L);
    initVH(&myHeap);

    insertFirst(&L,&myHeap,69);
    insertLast(&L,&myHeap,70);
    insertLast(&L,&myHeap,71);

    display(L,myHeap);

    delElem(&L,&myHeap,70);
    
    
    display(L,myHeap);

    return 0;
}

void initList(List *L){
    *L = -1;                                // Later used to point the first index used
}

void initVH(VirtualHeap *VH){
    VH->avail = 0;                          // Start with the first node as available
    for (int i = 0; i < MAX - 1; i++){
        VH->Nodes[i].link = i + 1;          // Link each node to the next one
    }
    VH->Nodes[MAX - 1].link = -1;           // End the list by setting last node's link to -1
}

int allocSpace(VirtualHeap *VH){
    List space = VH->avail;                     // Retrieve an available index
    if(space != -1){                            // IF not an invalid space (-1)
        VH->avail = VH->Nodes[space].link;      // Replace with a new available space
    }
    return space;                               // Return the index
}
void deAllocSpace(VirtualHeap *VH,int index){

    // Check if index within bounds
    if(index >= 0 && index < MAX){
        VH->Nodes[index].link = VH->avail;      // Set the old value of avail at the link variable of the index
        VH->avail = index;                      // Set the index to be the new available index
    }
}

void display(List L,VirtualHeap VH){
    List trav;
    for (trav = L; trav != -1; trav = VH.Nodes[trav].link){
        printf("%d ",VH.Nodes[trav].data);
    }
    printf("\n");
}

void insertFirst(List *L,VirtualHeap *VH,int num){
    // Check for space
    List space = allocSpace(VH);
    if(space != -1){
        VH->Nodes[space].data = num;            // Store the element

        // Insert at the beginning of the list
        VH->Nodes[space].link = *L;             // Link the new node to the old first node
        *L = space;                             // Update the head to the newly inserted node
    }
}

void insertLast(List *L,VirtualHeap *VH,int num){
    //Check for space
    List *trav;
    List space = allocSpace(VH);
    if(space != - 1){
        VH->Nodes[space].data = num;            // Store the element
        VH->Nodes[space].link = -1;
    }

    // Traverse
    for (trav = L; *trav != - 1; trav = &(VH->Nodes[*trav].link)){}

    // Insert the new element
    *trav = space;                              
}

void delElem(List *L,VirtualHeap *VH,int elem){
    List *trav;
    // Traverse
    for (trav = L; *trav != -1 && VH->Nodes[*trav].data != elem; trav = &(VH->Nodes[*trav].link)){}

    // If found
    if(*trav != -1){
        List temp = *trav;                  // Store temp in a temporary varaible
        *trav = VH->Nodes[temp].link;       // Set the link of the cell at index "temp" to trav
        deAllocSpace(VH,temp);              // Deallocate temp
    }
}