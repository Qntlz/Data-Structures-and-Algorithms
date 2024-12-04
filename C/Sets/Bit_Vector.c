#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    unsigned int *bits;  // Array of 32-bit words representing the bit vector
    int count;           // Count of elements in the set
} BitVector;

void initVector(BitVector*);
void insert(BitVector*, int);
void delete(BitVector*, int);
bool isMember(BitVector, int);
BitVector getUnion(BitVector, BitVector);
BitVector getIntersection(BitVector, BitVector);
BitVector getDifference(BitVector, BitVector);
void display(BitVector);

int main() {
    BitVector S1, S2, S3, S4, S5, S6;

    // Initialize BitVectors
    initVector(&S1);
    initVector(&S2);
    initVector(&S3);
    initVector(&S4);
    initVector(&S5);
    initVector(&S6);

    // Insert elements into sets
    insert(&S1, 1);
    insert(&S1, 2);
    insert(&S1, 3);

    insert(&S2, 3);
    insert(&S2, 4);
    insert(&S2, 5);

    printf("Set 1: ");
    display(S1);
    printf("Set 2: ");
    display(S2);

    // Perform union, intersection, and difference operations
    S4 = getUnion(S1, S2);
    printf("Union of Set 1 & Set 2: ");
    display(S4);

    S5 = getIntersection(S1, S2);
    printf("Intersection of Set 1 & Set 2: ");
    display(S5);

    S6 = getDifference(S1, S2);             // S1 - S2
    printf("Difference of Set 1 & Set 2: ");
    display(S6);

    return 0;
}

void initVector(BitVector *Set) {
    Set->count = 0;
    Set->bits = calloc((MAX + 31) / 32, sizeof(unsigned int));  // Allocate memory for enough 32-bit words
}

void insert(BitVector *Set, int elem) {
    if (elem < MAX) {
        Set->bits[elem / 32] |= (1 << (elem % 32));
        Set->count++;
    } else {
        printf("Element %d out of bounds\n", elem);
    }
}

void delete(BitVector *Set, int elem) {
    if (elem < MAX) {
        Set->bits[elem / 32] &= ~(1 << (elem % 32));
        Set->count--;  
    } else {
        printf("Element %d out of bounds\n", elem);
    }
}

bool isMember(BitVector Set, int elem) {
    return (elem < MAX) && (Set.bits[elem / 32] & (1 << (elem % 32)));
}

BitVector getUnion(BitVector SetA, BitVector SetB) {
    BitVector newSet;
    initVector(&newSet);
    int numWords = (MAX + 31) / 32; // Number of 32-bit words

    for (int i = 0; i < numWords; i++) {
        newSet.bits[i] = SetA.bits[i] | SetB.bits[i];
        newSet.count += __builtin_popcount(newSet.bits[i]);
    }
    return newSet;
}

BitVector getIntersection(BitVector SetA, BitVector SetB) {
    BitVector newSet;
    initVector(&newSet);
    int numWords = (MAX + 31) / 32;


    for (int i = 0; i < numWords; i++) {
        newSet.bits[i] = SetA.bits[i] & SetB.bits[i];
        newSet.count += __builtin_popcount(newSet.bits[i]);
    }
    return newSet;
}

BitVector getDifference(BitVector SetA, BitVector SetB) {
    BitVector newSet;
    initVector(&newSet);
    int numWords = (MAX + 31) / 32;

    for (int i = 0; i < numWords; i++) {
        newSet.bits[i] = SetA.bits[i] & ~SetB.bits[i];
        newSet.count += __builtin_popcount(newSet.bits[i]);
    }
    return newSet;
}

void display(BitVector Set) {
    printf("{ ");
    for (int i = 0; i < MAX; i++) {
        if (Set.bits[i / 32] & (1 << (i % 32))) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}
