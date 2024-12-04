#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node, *List;

typedef struct {
    List top;
} Set;

// Function to create a new node
Node* makeNode(int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Initialize the set
void initialize(Set *s) {
    s->top = NULL;
}

// Insert an element into the set in sorted order
void insertSorted(Set *s, int data) {
    if (s->top == NULL || s->top->data > data) {
        Node *newNode = makeNode(data);
        newNode->next = s->top;
        s->top = newNode;
        return;
    }

    Node *current = s->top;
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }
    
    if (current->data != data) { // Avoid duplicates
        Node *newNode = makeNode(data);
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Display the elements of the set
void display(Set *s) {
    Node *current = s->top;
    printf("{ ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("}\n");
}

// Union of two sorted sets
Set unionSets(Set *setA, Set *setB) {
    List last = NULL, tempA, tempB;
    Set newSet;

    for(initialize(&newSet),tempA = setA->top, tempB = setB->top;tempA != NULL && tempB != NULL;){
        List newNode = malloc(sizeof(Node));

        // A < B
        if(tempA->data < tempB->data && newNode != NULL){
            newNode->data = tempA->data;
            newNode->next = NULL;
            tempA = tempA->next;
        }
        // B < A
        else if(tempB->data < tempA->data && newNode != NULL){
            newNode->data = tempB->data;
            newNode->next = NULL;
            tempB = tempB->next;
        }
        // Both are same 
        else{
            newNode->data = tempA->data;
            newNode->next = NULL;
            tempA = tempA->next;
            tempB = tempB->next;
        }
         // Insert the new node into the result set
        if (newSet.top == NULL) {
            newSet.top = newNode;
        } else {
            last->next = newNode;
        }
        last = newNode;
    }

      // Add remaining elements from setA
    while (tempA != NULL) {
        List newNode = malloc(sizeof(Node));
        if (newNode == NULL) return newSet;  // Handle memory allocation failure
        newNode->data = tempA->data;
        newNode->next = NULL;
        if (newSet.top == NULL) {
            newSet.top = newNode;
        } else {
            last->next = newNode;
        }
        last = newNode;
        tempA = tempA->next;
    }

    // Add remaining elements from setB
    while (tempB != NULL) {
        List newNode = malloc(sizeof(Node));
        if (newNode == NULL) return newSet;  // Handle memory allocation failure
        newNode->data = tempB->data;
        newNode->next = NULL;
        if (newSet.top == NULL) {
            newSet.top = newNode;
        } else {
            last->next = newNode;
        }
        last = newNode;
        tempB = tempB->next;
    }


    return newSet;
}

// Example usage
int main() {
    Set set1, set2, result;

    initialize(&set1);
    initialize(&set2);

    insertSorted(&set1, 1);
    insertSorted(&set1, 3);
    insertSorted(&set1, 5);

    insertSorted(&set2, 2);
    insertSorted(&set2, 4);
    insertSorted(&set2, 6);

    printf("Set 1: ");
    display(&set1);
    printf("Set 2: ");
    display(&set2);

    result = unionSets(&set1, &set2);
    printf("Union: ");
    display(&result);

    return 0;
}
