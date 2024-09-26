#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Basic Linked List Implementation of Stack
// Stack: "LAST In, FIRST Out"

#define rogueVal -999 // Sentinel Value for invalid operations

// Define a linked list structure (Node)
typedef struct node
{
    int data;
    struct node *next;
} Node, *List;

// Define a Stack structure with a pointer to the top of the list
typedef struct
{
    List top;
} Stacktype, *Stack;

void initStack(Stack *);       // Initialize the Stack
int isEmpty(Stack);            // Check if the Stack is empty
void push(Stack *, int);       // Add item to the Stack
int pop(Stack *);              // Remove item from the Stack
void freeStack(Stack *);       // Free all nodes in the Stack
void peek(Stack);              // Display the top item in the Stack

int main()
{
    // Stack S is the main stack, tempStack is the temporary stack
    Stack S, tempStack;

    // Initialize both Stacks
    initStack(&S);
    initStack(&tempStack);

    // Push some values to Stack S
    for (int i = 0; i < 5; i++){
        push(&S, i + 1);                                             // Push values 1 to 5 into Stack S
    }
    printf("Top of the Original Stack(Stack S)\n");
    peek(S);

    // Display the Stack using pop and push to avoid traversal
    printf("\nDisplaying and storing elements in a temporary stack:\n");

    // Keep popping from Stack S until it's empty
    while (!isEmpty(S)) 
    {
        int hold = pop(&S);                                         // Pop element from Stack S
        printf("%d ", hold);                                        // Display the popped element
        push(&tempStack, hold);                                     // Push the element into tempStack to preserve it
    }
    printf("\n\n");

    // Now, restore the elements from tempStack back to the original Stack S
    printf("Restoring elements back to Stack S:\n");

    // Transfer elements back from tempStack to S
    while (!isEmpty(tempStack)) 
    {
        int hold = pop(&tempStack);                                // Pop from tempStack
        printf("%d ", hold);                                       // Display the element being pushed back
        push(&S, hold);                                            // Push back to original stack S
    }
    printf("\n");

    // Display the final top element of Stack S after restoration
    printf("\nFinal top element after restoring:\n");
    peek(S);                                                       // Display the top element

    // Free the allocated memory for both stacks
    freeStack(&S);
    freeStack(&tempStack);

    return 0;
}

// Function to initialize the Stack
void initStack(Stack *S)
{
    *S = malloc(sizeof(Stacktype));

    // Error checking to ensure memory was allocated
    if (*S != NULL){
        (*S)->top = NULL;                       // Set the top of the stack to NULL (empty stack)
    }
}

// Function to check if the Stack is empty
int isEmpty(Stack S)
{
    return (S->top == NULL);                    // The stack is empty if top is NULL
}

// Function to peek the top item in the Stack
void peek(Stack S)
{
    if (isEmpty(S)){
        printf("\nStack is empty.\n");
    }
    else{
        printf("Top: %d\n", S->top->data);      // Display the data at the top of the stack
    }
}

// Function to push an item onto the Stack
void push(Stack *S, int num)
{
    List newNode = malloc(sizeof(Node));

    // Check if memory allocation was successful
    if (newNode != NULL){
        newNode->data = num;                     // Assign data to the new node
        newNode->next = (*S)->top;               // Link the new node to the previous top
        (*S)->top = newNode;                     // Update top to the new node
    }
    else{
        printf("Memory allocation failed. Push operation aborted.\n");
    }
}

// Function to pop an item from the Stack
int pop(Stack *S)
{
    // Check if the Stack is empty before popping
    if (isEmpty(*S)){
        return rogueVal;                         // Return sentinel value if stack is empty
    }
    else{
        int hold = (*S)->top->data;             // Store data from the top node
        List temp = (*S)->top;                  // Temporarily store the top node
        (*S)->top = temp->next;                 // Move top to the next node in the stack
        free(temp);                             // Free the old top node
        return hold;                            // Return the popped value
    }
}

// Function to free all the nodes in the Stack
void freeStack(Stack *S)
{
    List temp;

    // Traverse the stack and free each node
    while ((*S)->top != NULL){
        temp = (*S)->top;
        (*S)->top = (*S)->top->next;
        free(temp);                             // Free the current node
    }
    free(*S);                                   // Free the stack structure itself
}
