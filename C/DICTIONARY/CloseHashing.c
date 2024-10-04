#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Dictionary (Close-Hashing)

#define MAX 7
#define EMPTY 0
#define DELETED -1

typedef int Dictionary;

void initDictionary(Dictionary*);
void insert(Dictionary*, int);
void delete(Dictionary*, int);
bool search(Dictionary*, int);
void display(Dictionary*);
int hash(int);


int main(){

    Dictionary A[MAX];
    int keys[] = {50, 51, 49, 16, 56, 15, 13};

    initDictionary(A);

    for (int i = 0; i < MAX; i++) {
        insert(A, keys[i]);
    }
    
    display(A);

    return 0;
}

void initDictionary(Dictionary *A) {
    for (int i = 0; i < MAX; i++) {
        A[i] = EMPTY;
    }
}

int hash(int key) {
    return key % 7;
}

void insert(Dictionary *A, int key) {
    int index = hash(key);

    // Linear Probing with wrapping
    int i;
    for (i = index; A[i] != EMPTY && A[i] != DELETED; i = (i + 1) % MAX) {}

    A[i] = key;
}

void delete(Dictionary *A, int key) {
    int index = hash(key);

    // Linear Probing with wrapping
    int i;
    for (i = index; A[i] != EMPTY; i = (i + 1) % MAX) {
        if (A[i] == key) {
            A[i] = DELETED;
            return;
        }
    }
}

bool search(Dictionary *A, int key) {
    int index = hash(key);

    // Linear Probing with wrapping
    int i;
    for (i = index; A[i] != EMPTY; i = (i + 1) % MAX) {
        if (A[i] == key) {
            return true;
        }
    }
    return false;
}

void display(Dictionary *A) {
    for (int i = 0; i < MAX; i++) {
        printf("%d\n", A[i]);
    }
}
