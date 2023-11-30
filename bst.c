#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to display the tree level-wise
void displayLevelWise(struct Node* root) {
    if (root == NULL)
        return;

    // Create a queue for level order traversal
    struct Node* queue[1000];
    int front = -1, rear = -1;

    // Enqueue the root
    queue[++rear] = root;

    while (front < rear) {
        struct Node* current = queue[++front];
        printf("%d ", current->data);

        // Enqueue left child
        if (current->left != NULL)
            queue[++rear] = current->left;

        // Enqueue right child
        if (current->right != NULL)
            queue[++rear] = current->right;
    }
}

// Function to insert a key into the binary tree
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    return root;
}

// Function to find the node with the minimum value in a binary tree (used for deletion)
struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        struct Node* temp = findMin(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to search for a key in the binary tree
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

// Function to create a mirror image of the binary tree
struct Node* mirrorImage(struct Node* root) {
    if (root == NULL)
        return root;

    // Swap the left and right subtrees
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recur for the left and right subtrees
    mirrorImage(root->left);
    mirrorImage(root->right);

    return root;
}

// Function to calculate the total height of the binary tree
int totalHeight(struct Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = totalHeight(root->left);
    int rightHeight = totalHeight(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to count the total number of nodes in the binary tree
int totalNodes(struct Node* root) {
    if (root == NULL)
        return 0;

    return 1 + totalNodes(root->left) + totalNodes(root->right);
}

// Function to count the total number of leaf nodes in the binary tree
int totalLeafNodes(struct Node* root) {
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return totalLeafNodes(root->left) + totalLeafNodes(root->right);
}

// Example usage
int main() {
    struct Node* root = NULL;

    // Insert elements into the binary tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Display the tree
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n\n");

    // Display the tree level-wise
    printf("Level-wise Display: ");
    displayLevelWise(root);
    printf("\n\n");

    // Search for a key
    int searchKey = 40;
    struct Node* searchResult = search(root, searchKey);
    if (searchResult != NULL)
        printf("Key %d found in the tree.\n\n", searchKey);
    else
        printf("Key %d not found in the tree.\n\n", searchKey);

    // Delete a key
    int deleteKey = 30;
    root = deleteNode(root, deleteKey);
    printf("Inorder Traversal after deletion: ");
    inorder(root);
    printf("\n\n");

    // Display the mirror image of the tree
    printf("Mirror Image: ");
    struct Node* mirroredRoot = mirrorImage(root);
    displayLevelWise(mirroredRoot);
    printf("\n\n");

    // Display total height of the tree
    printf("Total Height of the Tree: %d\n\n", totalHeight(root));

    // Display total number of nodes in the tree
    printf("Total Number of Nodes in the Tree: %d\n\n", totalNodes(root));

    // Display total number of leaf nodes in the tree
    printf("Total Number of Leaf Nodes in the Tree: %d\n\n", totalLeafNodes(root));


    return 0;
}
