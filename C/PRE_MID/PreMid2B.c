#include <stdio.h>
#include <stdlib.h>

// Task: Return a stack containing all multiples of 2

#define MAX 10
#define rogueVal -999

typedef struct node{
    int data;
    struct node *next;
}*Stack;

void initStack(Stack*);
void initDummy(Stack*);
void push(Stack*, int);
int pop(Stack*);
void peek(Stack);
Stack getMultiple(Stack*);

int main(){
    Stack S, multiStack;

    // Populate original Stack with dummy values
    initDummy(&S);
    peek(S);

    // Initialize multiStack             
    multiStack = getMultiple(&S);
    peek(multiStack);

    while(multiStack != NULL){
        printf("%d\n",pop(&multiStack));
    }    

    return 0;
}

void initStack(Stack *S){
    *S = NULL;
}

void initDummy(Stack *S){
    initStack(S);
                                                        // Populate Original Stack with Dummy Values
    for (int i = 0; i < MAX; i++){
        push(S, i + 1);
    }
}

void push(Stack *S, int num){
    Stack newNode = malloc(sizeof(struct node));
    if(newNode != NULL){
        newNode->data = num;
        newNode->next = *S;
    }
    *S = newNode;
}

int pop(Stack *S){
    if(*S == NULL){
        printf("Stack underflow\n");                    // Terminate if stack is empty
        return rogueVal;                                   
    }

    int hold = (*S)->data;
    Stack temp = *S;
    *S = temp->next;
    free(temp);
    return hold;
}

void peek(Stack S){
    if(S == NULL){
        printf("Stack is empty\n");
    } else {
        printf("Top: %d\n",S->data);
    }
}

Stack getMultiple(Stack *S){
    Stack newStack;
    initStack(&newStack);

    while (*S != NULL){                                 // Fix: check if the stack itself is empty
        int hold = (*S)->data;
        if(hold % 2 == 0){               
            push(&newStack, pop(S));                    // Pop from original stack and push to new stack
        } else {
            pop(S);                                     // Pop element if it's not a multiple of 2
        }
    }
    return newStack;
}
