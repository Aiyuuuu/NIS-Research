#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    // Allocate memory for a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1); // Exit if malloc fails
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertAtEnd(Node** head_ref, int data) {
    Node* newNode = createNode(data);
    
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
    
    // Link the new node to the end
    last->next = newNode;
}

// Function to reverse the linked list in-place
void reverseList(Node** head_ref) {
    Node* prev_node = NULL;
    Node* current_node = *head_ref;
    Node* next_node = NULL;

    // A list with 0 or 1 node is already reversed
    if (current_node == NULL || current_node->next == NULL) {
        return;
    }

    while (current_node != NULL) {
        // 1. Store the next node before we overwrite current_node->next
        next_node = current_node->next; 
        
        // 2. Reverse the pointer of the current node to point to the previous node
        current_node->next = prev_node; 
        
        // 3. Move pointers one position ahead for the next iteration
        prev_node = current_node;
        current_node = next_node;
    }
    
    // 4. After the loop, prev_node will be the new head of the reversed list
    *head_ref = prev_node;
}


// Function to print the linked list
void printList(Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Function to free all nodes in the list to prevent memory leaks
void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node* head = NULL; // Start with an empty list
    int num;

    printf("Enter numbers to build a linked list.\n");
    printf("Enter a non-numeric character to stop.\n");
    
    // Read numbers from the user until non-numeric input is entered
    while (scanf("%d", &num) == 1) {
        insertAtEnd(&head, num);
    }

    printf("\nOriginal List:\n");
    if (head == NULL) {
        printf("The list is empty.\n");
    } else {
        printList(head);
    }

    // Reverse the list
    reverseList(&head);

    printf("\nReversed List:\n");
    if (head == NULL) {
        printf("The list is empty.\n");
    } else {
        printList(head);
    }
    
    // Free the allocated memory
    freeList(head);
    
    return 0;
}
