#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 8

typedef struct {
    char lane[20];
    int time, priority;
} Traffic;

Traffic createTraffic(char*, int, int);
void initTraffic(Traffic*);
void exportTraffic(Traffic*);
Traffic* readTrafficFile();
void displayTraffic(Traffic);
void heapify(Traffic*, int n, int i);
int getPedxingTime(Traffic*);

int main() {
    Traffic dummyTraffic[MAX];
    Traffic* retrievedTraffic;

    initTraffic(dummyTraffic);              // Initialize Dummy Data
    exportTraffic(dummyTraffic);            // Export Dummy Data to "traffic.dat" file
    retrievedTraffic = readTrafficFile();   // Read data from "traffic.dat" file

    // Build a Min-Heap
    for (int i = (MAX / 2) - 1; i >= 0; i--) {
        heapify(retrievedTraffic, MAX, i);
    }

    // Uncomment to verify min-heap structure
    // for (int i = 0; i < MAX; i++) {
    //     printf("%d ", retrievedTraffic[i].priority);
    // }
    // printf("\n");

    int timeBeforeCross = getPedxingTime(retrievedTraffic);
    printf("Time before main pedestrian can cross (in seconds): %d\n", timeBeforeCross);

    // Free allocated memory for retrievedTraffic
    free(retrievedTraffic);

    return 0;
}

void heapify(Traffic* traffic, int numOfElements, int i) {
    int smallest = i;            // Initialize smallest as root
    int left = 2 * i + 1;        // Left child
    int right = 2 * i + 2;       // Right child

    // Check if left child exists and is smaller than root
    if (left < numOfElements && traffic[left].priority < traffic[smallest].priority) {
        smallest = left;
    }

    // Check if right child exists and is smaller than current smallest
    if (right < numOfElements && traffic[right].priority < traffic[smallest].priority) {
        smallest = right;
    }

    // If smallest is not root, swap and recursively heapify
    if (smallest != i) {
        Traffic temp = traffic[i];
        traffic[i] = traffic[smallest];
        traffic[smallest] = temp;
        heapify(traffic, numOfElements, smallest);
    }
}

void initTraffic(Traffic* myTraffic) {
    myTraffic[6] = createTraffic("main", 50, 1);
    myTraffic[2] = createTraffic("diversion", 50, 2);
    myTraffic[4] = createTraffic("main-left", 30, 3);
    myTraffic[7] = createTraffic("diversion-left", 30, 4);
    myTraffic[5] = createTraffic("main-right", 30, 5);
    myTraffic[1] = createTraffic("diversion-right", 30, 6);
    myTraffic[3] = createTraffic("main-pedxing", 20, 7);
    myTraffic[0] = createTraffic("diversion-pedxing", 20, 8);
}

Traffic createTraffic(char* lane, int time, int priority) {
    Traffic newTraffic;
    strcpy(newTraffic.lane, lane);
    newTraffic.time = time;
    newTraffic.priority = priority;
    return newTraffic;
}

void exportTraffic(Traffic* myTraffic) {
    FILE* fp = fopen("traffic.dat", "wb");
    if (fp != NULL) {
        fwrite(myTraffic, sizeof(Traffic), MAX, fp);
        fclose(fp);
    } else {
        fprintf(stderr, "Error: Could not open file for writing.\n");
    }
}

Traffic* readTrafficFile() {
    Traffic* retrievedTraffic = malloc(sizeof(Traffic) * MAX);
    FILE* fp = fopen("traffic.dat", "rb");
    if (fp != NULL) {
        fread(retrievedTraffic, sizeof(Traffic), MAX, fp);
        fclose(fp);
    } else {
        fprintf(stderr, "Error: Could not open file for reading.\n");
    }
    return retrievedTraffic;
}

int getPedxingTime(Traffic* myTraffic) {
    int timeBeforeCross = 0;
    int heapSize = MAX;

    while (heapSize > 0) {
        Traffic temp = myTraffic[0];

        if (strcmp(temp.lane, "main-pedxing") == 0) {
            break;
        }

        timeBeforeCross += temp.time;

        myTraffic[0] = myTraffic[heapSize - 1];
        heapSize--;

        heapify(myTraffic, heapSize, 0);
    }
    return timeBeforeCross;
}
