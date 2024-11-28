#include <stdio.h>
#include <stdbool.h>

// Binary Search with Different Versions

#define MAX 6
typedef int LIST[MAX];

bool binarySearch(int*,int,int);
bool binarySearchV2(LIST,int);

int main(){

    int elem = 4;

    // Version 1
    int arr[] = {1,2,3,4,5};
    printf("Is %d in the list? : %d\n\n",elem,binarySearch(arr,5,elem));

    // Version 2 (Size at index 0)
    int arr2[] = {5,1,2,4,7,9};                  
    printf("Is %d in the list? : %d\n\n",elem,binarySearchV2(arr2,elem));


    return 0;
}

bool binarySearch(int *arr,int size,int target){
    int mid,lb = 0,ub = size - 1;

    while (lb <= ub && arr[(mid = (lb+ub)/2)] != target){
        (arr[mid] > target) ? (ub = mid - 1) : (lb = mid + 1);
    }
    return lb <= ub;
}

bool binarySearchV2(LIST arr, int target){
    int mid, lb = 1, ub = arr[0];

    while (lb <= ub && arr[(mid = (lb + ub)/2)] != target){
        (target > arr[mid]) ? (lb = mid + 1) : (ub = mid - 1);
    }
    return lb <= ub;
}