#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Basic Array Implementation of Stack
// Stack: "LAST In, FIRST Out"

#define MAX 10
#define rogueVal -999 // Sentinel Value for invalid operations

typedef struct
{
    int top;               // Contains the index of the item at the top of the stack
    int arr[MAX];
} Stacktype, *Stack;

void initStack(Stack *);   // Initialize the stack
void push(Stack, int);     // Add an item to the stack
int pop(Stack);            // Remove an item from the stack
bool isEmpty(Stack);       // Check if the stack is empty
void peek(Stack);          // Display the top item
bool isFull(Stack);        // Check if the stack is full

int main()
{
    // Stack S is the main stack, tempStack is the temporary stack
    Stack S, tempStack; 

    // Initialize both stacks
    initStack(&S);
    initStack(&tempStack);

    // Push some values to Stack S
    for (int i = 0; i < 5; i++){
        push(S, i + 1); 
    }

    // Display the top of Stack S after pushing values
    printf("After pushing elements, ");
    peek(S);                                                               // Displays the top element

    // TASK: Print out the elements in Stack S
    // Use a temporary stack (tempStack) to store popped elements from Stack S
    printf("Elements in Stack S (from top to bottom):\n");
    
    while (!isEmpty(S))                                                    // Keep popping until Stack S is empty
    {
        int hold = pop(S);
        printf("%d ", hold);                                               // Print each element
        push(tempStack, hold);                                             // Push the popped element to tempStack to preserve it
    }
    printf("\n\n");

    // Now restore the elements from tempStack back to the original Stack S
    printf("Restoring elements back to Stack S:\n");

    // Transfer elements back from tempStack to S
    while (!isEmpty(tempStack))\
    {
        int hold = pop(tempStack);
        printf("%d ", hold);  
        push(S, hold);                                                       // Push back to original stack S
    }
    printf("\n");

    // Check the top of the stack again to confirm restoration
    printf("After restoring elements, ");
    peek(S);

    // Free the dynamically allocated memory
    free(S);
    free(tempStack);

    return 0;
}

void initStack(Stack *S)
{
    *S = malloc(sizeof(Stacktype));

    // Error Checking: Ensure memory allocation was successful
    if (*S != NULL){
        (*S)->top = -1;                                                     // Initialize the top index to -1 indicating an empty stack
    }
}

bool isEmpty(Stack S)
{
    return (S->top == -1);                                                  // A stack is empty when top is -1
}

bool isFull(Stack S)
{
    return (S->top == MAX - 1);                                             // A stack is full when top reaches MAX - 1
}

void push(Stack S, int n)
{
    // Check if the stack is full before pushing
    if (!isFull(S)){
        S->arr[++(S->top)] = n;                                             // Increment top and then assign value to the new top
    }
    else{
        printf("Stack Overflow: Cannot push %d, stack is full.\n", n);
    }
}

int pop(Stack S)
{
    // Check if the stack is empty before popping
    if (isEmpty(S)){
        printf("Stack Underflow: Cannot pop from an empty stack.\n");
        return rogueVal;                                                    // Return the sentinel value if pop fails
    }
    return S->arr[(S->top)--];                                              // Return the element and decrement the top index
}

void peek(Stack S)
{
    if (isEmpty(S)){
        printf("Stack is empty.\n");
    }
    else{
        printf("Top: %d\n", S->arr[S->top]);                                // Show the top element of the stack
    }
}
