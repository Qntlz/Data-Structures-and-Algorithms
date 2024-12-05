#include <stdio.h>
#include <stdlib.h>

/*
    Task:
        Create an Adjacency List of from the given Adjacency Label Matrix.

        Note:
        (u,v, Weight) is interpreted as (Parent,Child,Weight)

        The list should be displayed in the following order:

        Parent: (u) No. Edges: (count)
        Edges:
        Child: (v) Weight: (weight)

        Ex:
        Parent: 1 No. Edges: 2
        Edges:
        Child: 2  Weight: 25
        Child: 3  Weight: 45

*/

#define MAX 7
#define INF 999                         // Infinity

typedef int LabelAdjMat[MAX][MAX];          

// Edge Structure Definition
typedef struct node
{
    int child;
    int weight;
    struct node *next;
}Edge,*EdgePtr;

// Edge list structure definition
typedef struct{
    int parent;
    int count;
    EdgePtr edges;
}EdgeList;

// Adjacency list structure definiion
typedef struct{
    EdgeList myEdges[MAX];
} AdjacencyList;

void initList(AdjacencyList*);                          
AdjacencyList createAdjList(LabelAdjMat);
void displayList(AdjacencyList);

int main(){

    AdjacencyList myList;
    LabelAdjMat myMatrix = {
        {0,25,45,INF,INF,INF,INF},
        {INF,0,INF,50,60,55,INF},
        {INF,10,0,INF,INF,INF,70},
        {INF,INF,INF,0,INF,INF,INF},
        {INF,INF,65,20,0,30,INF},
        {INF,INF,INF,15,INF,0,INF},
        {INF,INF,INF,INF,40,35,0}
    };
    myList = createAdjList(myMatrix);
    displayList(myList);

    return 0;
}

void initList(AdjacencyList *myList){
    for (int i = 0; i < MAX; i++){
        myList->myEdges[i].parent = i + 1;
        myList->myEdges[i].count = 0;
        myList->myEdges[i].edges = NULL;
    }
    
}
AdjacencyList createAdjList(LabelAdjMat myMatrix){
    AdjacencyList newList;
    EdgePtr last = NULL;
    initList(&newList);
    
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            if(myMatrix[i][j] != INF && myMatrix[i][j] != 0 ){
                EdgePtr newEdge = malloc(sizeof(Edge));

                if(newEdge != NULL){
                    newEdge->child = j + 1;
                    newEdge->weight = myMatrix[i][j];
                    newEdge->next = NULL;
                    (last == NULL) ? (newList.myEdges[i].edges = newEdge) : (last->next = newEdge);
                    last = newEdge;
                    newList.myEdges[i].count++;
                }
            }
        }
        last = NULL;
    } 
    return newList;
}

void displayList(AdjacencyList myList){
    for (int i = 0; i < MAX; i++){
        printf("Parent: %d No. Edge: %d\n",myList.myEdges[i].parent,myList.myEdges[i].count);
        printf("Edges:\n");
        for (EdgePtr trav = myList.myEdges[i].edges; trav != NULL; trav = trav->next){
            printf("Child: %d  Weight: %d\n",trav->child, trav->weight);
        }
        printf("\n");
    }
}