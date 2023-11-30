#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the threaded binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded; // Flag to indicate whether right pointer is a thread or a child
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0; // Initially, the right pointer is a child, not a thread
    return newNode;
}

// Function to perform Inorder threading
void inorderThread(struct Node* root, struct Node** prev) {
    if (root) {
        inorderThread(root->left, prev);

        // If the previous node is threaded, make it point to the current node
        if (*prev && (*prev)->right == NULL) {
            (*prev)->right = root;
            (*prev)->isThreaded = 1;
        }

        // Update the previous pointer
        *prev = root;

        // If the right child is NULL, make it threaded to the inorder successor
        if (root->right == NULL) {
            root->right = *prev;
            root->isThreaded = 1;
        }

        inorderThread(root->right, prev);
    }
}

// Function to traverse the threaded binary tree in Inorder
void inorderTraversal(struct Node* root) {
    while (root) {
        // Find the leftmost node
        while (root->left)
            root = root->left;

        // Print the current node's data
        printf("%d ", root->data);

        // If the right pointer is a thread, move to the inorder successor
        if (root->isThreaded)
            root = root->right;
        else {
            // Otherwise, move to the leftmost node of the right subtree
            root = root->right;
            while (root && !root->isThreaded)
                root = root->left;
        }
    }
}

// Function to traverse the threaded binary tree in Postorder
void postorderTraversal(struct Node* root) {
    if (root) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);

        // Print the current node's data
        printf("%d ", root->data);
    }
}

int main() {
    // Create a sample threaded binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    // Perform Inorder threading
    struct Node* prev = NULL;
    inorderThread(root, &prev);

    // Traverse the threaded binary tree in Inorder
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Traverse the threaded binary tree in Postorder
    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
