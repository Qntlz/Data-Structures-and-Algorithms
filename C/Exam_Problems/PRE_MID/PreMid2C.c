#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Task: Determine if the school ID is in ascending order return TRUE if yes, FALSE is not

#define MAX 10    // Maximum number of students
#define NAMES 5   // Number of dummy names available

typedef enum { FALSE, TRUE } Boolean;

typedef struct {
    char fName[20], lName[20], mName;
} Name;

typedef struct {
    Name myName;
    int schoolID;
} StudentStruct, *Student;

typedef struct {
    Student myStudents[MAX];
    int count;
} StudRecords;

typedef struct {
    int front, rear;
    StudRecords myRecords;
} QueueType, *Queue;

void initQueue(Queue*);
void populateDummy(Queue*);
Boolean isAscending(Queue);

int main() {
    Queue myQueue;

    // Initialize Queue
    initQueue(&myQueue);
    populateDummy(&myQueue);

    // // Print the first student's first name to verify correctness
    // printf("%s\n", myQueue->myRecords.myStudents[myQueue->front]->myName.fName);

    // Check if the student ID's are in ascending order
    (isAscending(myQueue)) ? printf("Ascending Order") : printf("Not Ascending Order");

    free(myQueue); // Free the queue

    return 0;
}

void initQueue(Queue *Q) {
    *Q = malloc(sizeof(QueueType));   // Allocate memory for QueueType
    
    if (*Q != NULL) {
        (*Q)->front = (*Q)->rear = -1;  // Initialize front and rear to NULL
        (*Q)->myRecords.count = 0;        // Initialize count
    }
}

void populateDummy(Queue *Q) {
    // Dummy Values
    char *fNames[] = {"Lance", "Carl", "Walter", "Shawn", "Klyde"};
    char *lNames[] = {"Cerenio", "Omega", "Caballero", "Mayol", "Perante"};
    char mNames[] = {'M', 'A', 'B', 'C', 'D'};
    int studID[] = {1,2,3,4,5};              // Change this to check if the code is working

    int ctr;

    for (int i = 0; i < NAMES; i++) { 

        // Check if the queue is empty
        if((*Q)->front == -1){
            ctr = (*Q)->front = (*Q)->rear = 0;
        }
        else{
            ctr = (*Q)->rear = ((*Q)->rear + 1) % MAX;
        }

        // Allocate memory for a new student
        (*Q)->myRecords.myStudents[ctr] = malloc(sizeof(StudentStruct));
        
        if ((*Q)->myRecords.myStudents[ctr] == NULL) {
            printf("Memory allocation failed.\n");
        }

        // Assign values to the student
        strcpy((*Q)->myRecords.myStudents[ctr]->myName.fName, fNames[i]);
        (*Q)->myRecords.myStudents[ctr]->myName.mName = mNames[i];
        strcpy((*Q)->myRecords.myStudents[ctr]->myName.lName, lNames[i]);
        (*Q)->myRecords.myStudents[ctr]->schoolID = studID[i];

        // Increment the student count
        (*Q)->myRecords.count++;
      
    }
}

Boolean isAscending(Queue Q) {
    if (Q->front == -1) {
        return FALSE;  // Queue is empty
    }

    // Create a tempory front
    int tempFront = Q->front;

    while (tempFront != Q->rear) {
        int firstHold = Q->myRecords.myStudents[tempFront]->schoolID;       // Retrieve data of the current front
        int nextIndex = (tempFront + 1) % MAX;                              // Update front (Assuming we dequeue)
        int secondHold = Q->myRecords.myStudents[nextIndex]->schoolID;      // Retrieve data of the new current front

        // If the current element is greater than the next, the order is not ascending
        if (firstHold > secondHold) {
            return FALSE;
        }

        // Move to the next element
        tempFront = nextIndex;
    }

    return TRUE;  // The queue is in ascending order
}

