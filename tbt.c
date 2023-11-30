#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the threaded binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded; // Flag to indicate whether the right pointer is a thread
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0; // Initially, the right pointer is not a thread
    return newNode;
}

// Function to perform inorder threading
void threadedInorder(struct Node* root, struct Node** prev) {
    if (root != NULL) {
        // Recur for the left subtree
        threadedInorder(root->left, prev);

        // If the current node's left child is NULL, thread it to the predecessor
        if (root->left == NULL) {
            root->left = *prev;
            root->isThreaded = 1;
        }

        // If the predecessor's right child is NULL, thread it to the current node
        if (*prev != NULL && (*prev)->right == NULL && !(*prev)->isThreaded) {
            (*prev)->right = root;
        }

        // Update the predecessor to the current node
        *prev = root;

        // Recur for the right subtree
        threadedInorder(root->right, prev);
    }
}

// Function to traverse the threaded binary tree in postorder
void threadedPostorder(struct Node* root) {
    if (root != NULL) {
        // Recur for the left subtree
        threadedPostorder(root->left);

        // Recur for the right subtree
        threadedPostorder(root->right);

        // Process the current node
        printf("%d ", root->data);
    }
}

// Function to traverse the threaded binary tree in preorder
void threadedPreorder(struct Node* root) {
    if (root != NULL) {
        // Process the current node
        printf("%d ", root->data);

        // Recur for the left subtree
        threadedPreorder(root->left);

        // Recur for the right subtree
        threadedPreorder(root->right);
    }
}

// Function to traverse the threaded binary tree in inorder
void threadedInorderTraversal(struct Node* root) {
    struct Node* current = root;

    // Find the leftmost node in the threaded binary tree
    while (current->left != NULL)
        current = current->left;

    // Traverse the threaded binary tree
    while (current != NULL) {
        printf("%d ", current->data);

        // If the right pointer is a thread, move to the inorder successor
        if (current->isThreaded)
            current = current->right;
        else {
            // Move to the leftmost node of the right subtree
            current = current->right;
            while (current != NULL && current->left != NULL)
                current = current->left;
        }
    }
}

// Example usage
int main() {
    // Create nodes for the threaded binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Perform inorder threading
    struct Node* prev = NULL;
    threadedInorder(root, &prev);

    // Traverse the threaded binary tree in postorder
    printf("Postorder Traversal: ");
    threadedPostorder(root);
    printf("\n");

    // Traverse the threaded binary tree in preorder
    printf("Preorder Traversal: ");
    threadedPreorder(root);
    printf("\n");

    // Traverse the threaded binary tree in inorder
    printf("Inorder Traversal: ");
    threadedInorderTraversal(root);
    printf("\n");

    return 0;
}
