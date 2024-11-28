#include <stdio.h>

void heapifySubTree(int*,int,int);
void heapifyTree(int*,int);
void printArray(int*,int);

int main() {
    int arr[] = {4, 10, 3, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    heapifyTree(arr, n);

    printf("Heapified array (Max-Heap):\n");
    printArray(arr, n);

    return 0;
}

// Function to heapify a subtree rooted at node `i`
void heapifySubTree(int arr[], int n, int i) {
    int largest = i;           // Initialize largest as root
    int left = 2 * i + 1;      // Left child index
    int right = 2 * i + 2;     // Right child index

    // Check if left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Check if right child is larger than the largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected subtree
        heapifySubTree(arr, n, largest);
    }
}

// Function to build a max-heap from the array
void heapifyTree(int arr[], int n) {
    // Start from the last non-leaf node and heapify each subtree
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifySubTree(arr, n, i);
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

