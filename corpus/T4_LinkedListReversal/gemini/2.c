#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    // Allocate memory for the new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1); // Exit if memory allocation fails
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add a node to the end (tail) of the list
void appendNode(Node** head_ref, int new_data) {
    Node* newNode = createNode(new_data);

    // If the list is empty, the new node becomes the head
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }

    // Otherwise, traverse to the last node
    Node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }

    // Change the next of the last node
    last->next = newNode;
}

// Function to reverse the linked list
void reverseList(Node** head_ref) {
    Node* prev = NULL;
    Node* current = *head_ref;
    Node* next = NULL;

    while (current != NULL) {
        // Store the next node before we overwrite current->next
        next = current->next;
        
        // Reverse the current node's pointer to point to the previous node
        current->next = prev;
        
        // Move pointers one position ahead for the next iteration
        prev = current;
        current = next;
    }
    
    // After the loop, 'prev' will be the new head of the reversed list
    *head_ref = prev;
}

// Function to print the linked list
void printList(Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Function to free the memory used by the linked list
void freeList(Node** head_ref) {
    Node* current = *head_ref;
    Node* next;
    while (current != NULL) {
        next = current->next; // Save the next node
        free(current);        // Free the current node
        current = next;       // Move to the next node
    }
    *head_ref = NULL; // Set the head to NULL to avoid dangling pointers
}

// Main function to drive the program
int main() {
    Node* head = NULL;
    int number;

    printf("Enter integer numbers to build the linked list.\n");
    printf("Type any non-numeric character (e.g., 'q') to stop.\n");

    // Read numbers from standard input and append them to the list
    while (scanf("%d", &number) == 1) {
        appendNode(&head, number);
    }

    printf("\nOriginal list:\n");
    if (head == NULL) {
        printf("The list is empty.\n");
    } else {
        printList(head);
    }

    // Reverse the list
    reverseList(&head);

    printf("\nReversed list:\n");
    if (head == NULL) {
        printf("The list is empty.\n");
    } else {
        printList(head);
    }
    
    // Free the allocated memory before exiting
    freeList(&head);
    
    printf("\nMemory has been freed.\n");

    return 0;
}
