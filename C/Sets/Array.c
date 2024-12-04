#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Array Implementation of SET UID

#define MAX 5

typedef struct
{
    int elements[MAX];
    int size;
} SetArray, *SET;

void initSet(SET *);
bool isMember(SET, int);
void insert(SET, int);
void delete(SET, int);
void display(SET);
SET getUnion(SET,SET);
SET getIntersection(SET,SET);
SET getDifference(SET,SET);

int main()
{

    SET A,B,unionSet,interSet, DiffSet;

    // Initialize Set
    initSet(&A);
    initSet(&B);

    // Insert Data
    insert(A, 1);
    insert(A, 2);
    insert(A, 3);
    insert(A, 4);

    insert(B, 2);
    insert(B, 3);
    insert(B, 5);

    printf("Current Set A: ");
    display(A);

    delete(A,4);

    printf("Current Set A (After Deletion): ");
    display(A);

    printf("Current Set B: ");
    display(B);

    unionSet = getUnion(A,B);
    interSet = getIntersection(A,B);
    DiffSet = getDifference(A,B);

    printf("Union of Set A & B: ");
    display(unionSet);

    printf("Intersection of Set A & B: ");
    display(interSet);

    printf("Difference of Set A & B: ");
    display(DiffSet);

    free(A);
    free(B);
    free(unionSet);
    free(interSet);
    free(DiffSet);

    return 0;
}

void initSet(SET *A){
    *A = malloc(sizeof(SetArray));

    if (*A != NULL){
        (*A)->size = 0;
    }
}

bool isMember(SET S, int elem){
    for (int i = 0; i < S->size; i++){
        if (S->elements[i] == elem){
            return true;
        }
    }
    return false;
}

void display(SET S){
    for (int i = 0; i < S->size; i++){
        printf("%d ", S->elements[i]);
    }
    printf("\n");
}

void insert(SET S, int elem){
    // Check for space
    if (S->size < MAX){
        if(!isMember(S,elem)){
            S->elements[S->size++] = elem;
        }
        else{
            printf("Element Already Present in Set\n");
        }
    }
    else{
        printf("SET IS FULL\n");
    }
}

void delete(SET S, int elem){
    for (int i = 0; i < S->size; i++){
        if (S->elements[i] == elem){
            for (int j = i; j < S->size; j++){
                S->elements[j] = S->elements[j + 1];
            }
            S->size--;
            break;
        }
    }
}

SET getUnion(SET A, SET B){
    SET newSet = malloc(sizeof(SetArray));

    initSet(&newSet);

    if(newSet != NULL){
        int i = 0, j = 0;
        while(i < A->size && j < B->size){
            if(A->elements[i] < B->elements[j]){
                insert(newSet,A->elements[i++]);
            }
            else if(A->elements[i] > B->elements[j]){
                insert(newSet,B->elements[j++]);
            }
            else{
                insert(newSet,A->elements[i++]);
                j++;
            }
        }

        for (; i < A->size; i++){
            insert(newSet,A->elements[i]);
        }

        for (; j < B->size; j++){
            insert(newSet,B->elements[j]);
        }
    }

    return newSet;
}

SET getIntersection(SET A,SET B){
    SET newSet = malloc(sizeof(SetArray));

    if(newSet != NULL){
        initSet(&newSet);

        for (int i = 0; i < A->size; i++){
            if(isMember(B,A->elements[i])){
                insert(newSet,A->elements[i]);
            }
        }
    }
    return newSet;
}
SET getDifference(SET A,SET B){
    SET newSet = malloc(sizeof(SetArray));

    if(newSet != NULL){
        initSet(&newSet);

        for (int i = 0; i < A->size; i++){
            if(!isMember(B,A->elements[i])){
                insert(newSet,A->elements[i]);
            }
        }
    }
    return newSet;
}
