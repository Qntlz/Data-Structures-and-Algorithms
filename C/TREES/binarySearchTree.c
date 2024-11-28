#include <stdio.h>
#include <stdlib.h>

/*
    Binary Search Tree
    - Binary search tree follows all properties of binary tree and for every nodes, 
    its left subtree contains values less than the node and the right subtree contains 
    values greater than the node. 
*/

// Define the structure of a tree node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node, *NodePtr;

NodePtr createNode(int);                    // Function to create a new node
void insert(NodePtr*, int);                 // Recursive function to insert a new node into the BST
void delete(NodePtr,int);                   // Function to delete an element
void inOrder(NodePtr);                      // In-order traversal (left, root, right)
void preOrder(NodePtr);                     // Pre-order traversal (root, left, right)
void postOrder(NodePtr);                    // Post-order traversal (left, right, root)
void freeTree(NodePtr);                     // Free all nodes in the tree

int main() {
    NodePtr root = NULL;
    int x;

    // Input data for the BST
    printf("Enter integers to insert into the BST (-1 to stop):\n");
    while (1) {
        scanf("%d", &x);
        if (x == -1) break;
        insert(&root, x);
    }

    // Traversals
    printf("\nIn-order Traversal: ");
    inOrder(root);
    printf("\nPre-order Traversal: ");
    preOrder(root);
    printf("\nPost-order Traversal: ");
    postOrder(root);

    while (1){
        printf("Enter element to be deleted: ");
        scanf("%d", &x);
        if(x == -1) break;
        delete(root,x);
    }
    
    // Traversals
    printf("\nIn-order Traversal: ");
    inOrder(root);
    printf("\nPre-order Traversal: ");
    preOrder(root);
    printf("\nPost-order Traversal: ");
    postOrder(root);


    // Free the tree
    freeTree(root);
    printf("\n\nTree memory has been freed.\n");

    return 0;
}

NodePtr createNode(int data) {
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(NodePtr *root, int data) {
    // Base Case
    if (*root == NULL) {
        *root = createNode(data);
        return;
    }

    if (data < (*root)->data) {
        insert(&(*root)->left, data);
    } else {
        insert(&(*root)->right, data);
    }
}

void delete(NodePtr root, int elem) {
    NodePtr prev = NULL;

    // Step 1: Search for the node
    while (root != NULL && root->data != elem) {
        prev = root;
        root = (elem < root->data) ? root->left : root->right;
    }

    // Step 2: Node Found
    if (root != NULL) {
        // Case 1: Leaf Node
        if (root->left == NULL && root->right == NULL) {
            if (prev == NULL) {
                // Root node case
                free(root);
                root = NULL;
            } else {
                (prev->left == root) ? (prev->left = NULL) : (prev->right = NULL);
                free(root);
            }
        }
        // Case 2: One Child
        else if (root->left == NULL || root->right == NULL) {
            NodePtr child = (root->left != NULL) ? root->left : root->right;
            if (prev == NULL) {
                // Root node case
                free(root);
                root = child;
            } else {
                (prev->left == root) ? (prev->left = child) : (prev->right = child);
                free(root);
            }
        }
        // Case 3: Two Children
        else {
            // Find the in-order successor
            NodePtr trav = root->right;
            NodePtr successorParent = root; // Keep track of the successor's parent

            while (trav->left != NULL) {
                successorParent = trav;
                trav = trav->left;
            }

            // Replace root's data with successor's data
            root->data = trav->data;

            // Delete the successor
            if (successorParent->left == trav) {
                successorParent->left = trav->right; // Bypass successor
            } else {
                successorParent->right = trav->right;
            }
            free(trav);
        }
    }
}


void inOrder(NodePtr root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}


void preOrder(NodePtr root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(NodePtr root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}


void freeTree(NodePtr root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

