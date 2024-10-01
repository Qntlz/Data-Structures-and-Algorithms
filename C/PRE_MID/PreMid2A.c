#include <stdio.h>
#include <stdlib.h>

// Topic: Cursor-based
// Task: Return a cursorList containing even numbers from the original cursorList

#define MAX 0xA // 10 in hexadecimal

typedef struct {
    int data, link;
} Cell;

typedef struct {
    Cell Nodes[MAX];
    int avail;
} *VirtualHeap;

typedef struct {
    VirtualHeap VH;
    int top;
} CursorList;

void initTop(CursorList*);
void initVH(CursorList*);
int allocSpace(CursorList*);
void deAllocSpace(CursorList*, int);
CursorList getEven(CursorList);

int main() {
    CursorList myCursor, evenCursor;

    initTop(&myCursor);
    initVH(&myCursor);

    // Original list
    printf("Original list:\n");
    for (int i = myCursor.top; i != -1; i = myCursor.VH->Nodes[i].link){
        printf("Data: %d   Link: %d\n",myCursor.VH->Nodes[i].data,myCursor.VH->Nodes[i].link);
    }

    // Even numbers only
    evenCursor = getEven(myCursor);
    printf("\nEven number list:\n");
    for (int i = evenCursor.top; i != -1; i = evenCursor.VH->Nodes[i].link) {
        printf("Data: %d   Link: %d\n", evenCursor.VH->Nodes[i].data, evenCursor.VH->Nodes[i].link);
    }

    return 0;
}

void initTop(CursorList *L) {
    L->top = -1; 
}

void initVH(CursorList *L) {
    L->VH = (VirtualHeap) malloc(sizeof(struct{Cell Nodes[MAX];int avail;}));
    L->VH->avail = 0;  // Initialize 'avail' to 0
    
    // Populate Dummy Values & Link
    for (int ctr = 0; ctr < MAX - 1; ctr++) {
        L->VH->Nodes[ctr].data = ctr + 1;   // Assign data
        L->VH->Nodes[ctr].link = ctr + 1;   // Link to the next node
        if(L->top == -1){
            L->top = ctr;   // Set top to the first element
        }
    }
    
    L->VH->Nodes[MAX - 1].data = MAX;      // Assign the data for the last node
    L->VH->Nodes[MAX - 1].link = -1;       // End of the list should link to -1 
}

int allocSpace(CursorList *L){
    int space = L->VH->avail;
    if (space != -1){
        L->VH->avail =  L->VH->Nodes[space].link;
    }
    return space;
}

void deAllocSpace(CursorList *L, int index){
    // Check if index is within bounds
    if (index >= 0 && index < MAX){
        L->VH->Nodes[index].link = L->VH->avail;
        L->VH->avail = index;
    }
}

CursorList getEven(CursorList L){
    CursorList newCursor;
    
    initTop(&newCursor);
    newCursor.VH = (VirtualHeap) malloc(sizeof(struct{Cell Nodes[MAX];int avail;}));
    newCursor.VH->avail = 0;  // Initialize 'avail' to 0

    // Link Cells of the new Cursor
    for (int i = 0; i < MAX; i++){
        newCursor.VH->Nodes[i].link = i + 1;
    }
    newCursor.VH->Nodes[MAX -1].data = -1;
    
    
    int prev = -1; // To keep track of the last inserted node

    // Traverse the original cursorList
    for (int trav = L.top; trav != -1; trav = L.VH->Nodes[trav].link){
        int tempData = L.VH->Nodes[trav].data;

        if (tempData % 2 == 0) {
            int space = allocSpace(&newCursor);
            if (space != -1) {
                newCursor.VH->Nodes[space].data = tempData;
                if (prev == -1) {
                    newCursor.top = space;  // Set the top for the first even element
                } else {
                    newCursor.VH->Nodes[prev].link = space;  // Link the previous node to the new one
                }
                prev = space;  // Update the previous node
            }
        }
    }
    
    // End the list with -1
    if (prev != -1) {
        newCursor.VH->Nodes[prev].link = -1;
    }
    
    return newCursor;
}
