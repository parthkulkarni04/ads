/*to merge two sorted Doubly linked lists and display their result.
#include <stdio.h>
#include <stdlib.h>

// Node structure for a doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of a doubly linked list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to merge two sorted doubly linked lists
struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* mergedList = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            insertEnd(&mergedList, list1->data);
            list1 = list1->next;
        } else {
            insertEnd(&mergedList, list2->data);
            list2 = list2->next;
        }
    }

    // If there are remaining elements in list1
    while (list1 != NULL) {
        insertEnd(&mergedList, list1->data);
        list1 = list1->next;
    }

    // If there are remaining elements in list2
    while (list2 != NULL) {
        insertEnd(&mergedList, list2->data);
        list2 = list2->next;
    }

    return mergedList;
}

// Function to display a doubly linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    // Insert elements into the first sorted doubly linked list
    insertEnd(&list1, 1);
    insertEnd(&list1, 3);
    insertEnd(&list1, 5);

    // Insert elements into the second sorted doubly linked list
    insertEnd(&list2, 2);
    insertEnd(&list2, 4);
    insertEnd(&list2, 6);

    printf("First Sorted Doubly Linked List: ");
    displayList(list1);

    printf("Second Sorted Doubly Linked List: ");
    displayList(list2);

    struct Node* mergedList = mergeSortedLists(list1, list2);

    printf("Merged Sorted Doubly Linked List: ");
    displayList(mergedList);

    return 0;
}*/
/*to create doubly linked list and perform following operations on it. A) Insert (all cases) 2. Delete (all cases).
#include <stdio.h>
#include <stdlib.h>

// Node structure for a doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of a doubly linked list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to insert a node at the end of a doubly linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to insert a node after a given node in a doubly linked list
void insertAfterNode(struct Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }

    struct Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    newNode->prev = prevNode;
    prevNode->next = newNode;

    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
}

// Function to delete a node by key from a doubly linked list
void deleteByKey(struct Node** head, int key) {
    struct Node* current = *head;

    // Find the node with the given key
    while (current != NULL && current->data != key) {
        current = current->next;
    }

    // If the key is not found
    if (current == NULL) {
        printf("Key not found in the list\n");
        return;
    }

    // Update pointers to skip the node to be deleted
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
}

// Function to display a doubly linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* list = NULL;

    // Insert at the beginning
    insertAtBeginning(&list, 1);
    insertAtBeginning(&list, 2);
    printf("Doubly Linked List after insert at the beginning: ");
    displayList(list);

    // Insert at the end
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 4);
    printf("Doubly Linked List after insert at the end: ");
    displayList(list);

    // Insert after a node
    struct Node* nodeToInsertAfter = list->next;
    insertAfterNode(nodeToInsertAfter, 5);
    printf("Doubly Linked List after insert after a node: ");
    displayList(list);

    // Delete by key
    deleteByKey(&list, 3);
    printf("Doubly Linked List after delete by key: ");
    displayList(list);

    return 0;
}

*/