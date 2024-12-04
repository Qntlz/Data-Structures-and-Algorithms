#include <stdio.h>
#include <stdlib.h>

/*
    Binary Trees 
        - Can maximum have 2 childrens
    
    Types of Traversals
    Pre-order
        - Root -> Left -> Right
    Inorder
        - Left -> Root -> Right
    Post-order
        - Left -> Right -> Root
*/ 

// Definition for Tree Structure
typedef struct node{                        
    char data;
    struct node *left, *right;
} TreeNode, *TreeNodePtr;

typedef struct {
    TreeNodePtr root;
}BinaryTree;


TreeNodePtr buildTree();                           
void displayPreOrder(TreeNodePtr);
void displayPostOrder(TreeNodePtr);
void displayInorder(TreeNodePtr);

int main()
{

    BinaryTree myTree;
    myTree.root = buildTree();

    printf("Pre-Order Traversal: ");
    displayPreOrder(myTree.root);
    printf("\n");

    printf("Inorder Traversal: ");
    displayInorder(myTree.root);
    printf("\n");

    printf("Post-Order Traversal: ");
    displayPostOrder(myTree.root);
    printf("\n");

    return 0;
}

TreeNodePtr buildTree(){
    TreeNodePtr newNode = malloc(sizeof(TreeNode));

    if (newNode != NULL){
        char x;
        printf("Enter data ($ for no data):");
        scanf(" %c", &x);

        // Base Case
        if (x == '$'){
            return NULL;
        }

        newNode->data = x;
        printf("Left:\n");
        newNode->left = buildTree();
        printf("Right:\n");
        newNode->right = buildTree();
    }
    return newNode;
}

void displayPreOrder(TreeNodePtr root){
    if(root != NULL){
        printf("%c ",root->data);
        displayPreOrder(root->left);
        displayPreOrder(root->right);
    }
}

void displayPostOrder(TreeNodePtr root){
    if(root != NULL){
        displayPostOrder(root->left);
        displayPostOrder(root->right);
        printf("%c ",root->data);
    }
}

void displayInorder(TreeNodePtr root){
    if(root != NULL){
        displayInorder(root->left);
        printf("%c ",root->data);
        displayInorder(root->right);
    }
}