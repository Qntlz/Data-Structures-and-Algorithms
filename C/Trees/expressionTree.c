#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 5
#define MAX 20
#define rogueVal -999

/*
    Topic: Using Binary Tree and stack to solve a arithmetic expression

    Task:  
          Create a binary tree for this arithmetic expression
                        (54 + 37) / (72 - 5 *)
          and display the result for the given expression.

    Requirements:
        - Must use Binary Trees & Stack
*/ 

typedef struct node{
    char data[5];
    struct node *left,*right;
}TreeNode,*TreeNodePtr;

typedef struct{
    TreeNodePtr root;
}BinaryTree;

typedef struct{
    int top;
    int arr[MAX];
} Stacktype, *Stack;

TreeNodePtr create();
void initStack(Stack*);
bool isFull(Stack);
bool isEmpty(Stack);
void push(Stack,int);
int pop(Stack);
void postOrderTraversal(TreeNodePtr, Stack);
void performOperation(Stack, char*);

int main(){

    BinaryTree myTree;
    Stack s;
    initStack(&s);
    myTree.root = create();
    postOrderTraversal(myTree.root,s);

    printf("\nResult: %d\n",s->arr[s->top]);

    return 0;
}

TreeNodePtr create(){
    TreeNodePtr newNode = malloc(sizeof(TreeNode));

    if(newNode != NULL){
        char str[MAX];
        printf("Enter data(-1 for no data): ");
        fgets(str,MAX_LEN,stdin);
        str[strlen(str) - 1] = '\0';
        
        if(strcmp(str,"-1") == 0){
            return NULL;
        }

        strcpy(newNode->data,str);
        printf("Left: \n");
        newNode->left = create();
        printf("Right: \n");
        newNode->right = create();
    }
    return newNode;
}

void postOrderTraversal(TreeNodePtr root, Stack s){
    if(root == NULL){
        return;
    }

    postOrderTraversal(root->left,s);
    postOrderTraversal(root->right,s);
    if(atoi(root->data) == 0){
        performOperation(s,root->data);
    }
    else{
        push(s,atoi(root->data));
    }
}

void initStack(Stack *s){
    *s = malloc(sizeof(Stacktype));

    if(*s != NULL){
        (*s)->top = -1;
    }
}

bool isFull(Stack s){
    return (s->top == MAX - 1);                                             // A stack is full when top reaches MAX - 1
}

bool isEmpty(Stack s){
    return (s->top == -1);
}

int pop(Stack s){
    if(!isEmpty(s)){
        return s->arr[(s->top)--];
    }
    else{
        printf("Stack is EMPTY\n");
    }
    return rogueVal;
}

void push(Stack s,int num){
    if(!isFull(s)){
       s->arr[++(s->top)] = num;
    }
    else{
        printf("Stack is FULL!\n");
    }
}

void performOperation(Stack s,char *operand){
    int result;
    
    if(strcmp(operand,"+") == 0){
        result = pop(s);
        result += pop(s);
    }
    else if(strcmp(operand,"-") == 0){
        int temp = pop(s);                  // Store the first pop element in temporary variable
        result = pop(s);
        result -= temp;
    }
    else if(strcmp(operand,"*") == 0){
        result = pop(s);
        result *= pop(s);
    }
    else if(strcmp(operand,"/") == 0){
        int temp = pop(s);                  // Store the first pop element in temporary variable
        result = pop(s);
        result /= temp;
    }
    push(s,result);
}
