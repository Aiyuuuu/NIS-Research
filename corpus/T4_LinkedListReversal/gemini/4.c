#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the singly linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function Prototypes
Node* createNode(int data);
void insertAtTail(Node** headRef, int data);
void reverseList(Node** headRef);
void printList(Node* head);
void freeList(Node** headRef);

/**
 * main: The entry point of the program.
 * It reads integers, builds a list, reverses it, prints it, and cleans up.
 */
int main() {
    Node* head = NULL;
    int n, value;

    // 1. Read input and build the list
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input for number of elements.\n");
        return 1;
    }

    if (n > 0) {
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            if (scanf("%d", &value) != 1) {
                printf("Invalid integer input.\n");
                freeList(&head); // Clean up what was already allocated
                return 1;
            }
            insertAtTail(&head, value);
        }
    }


    // 2. Print the original list for verification
    printf("\nOriginal list: ");
    printList(head);

    // 3. Call the function to reverse the list
    reverseList(&head);

    // 4. Print the reversed list
    printf("Reversed list: ");
    printList(head);
    
    // 5. Free the allocated memory to prevent memory leaks
    freeList(&head);

    return 0;
}

/**
 * createNode: Allocates a new node with the given data.
 * @param data The integer value for the new node.
 * @return A pointer to the newly created node.
 */
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
 * insertAtTail: Adds a new node at the end of the list.
 * @param headRef A pointer to the head pointer of the list.
 *                This allows modification of the head itself if the list is empty.
 * @param data The integer value for the new node.
 */
void insertAtTail(Node** headRef, int data) {
    Node* newNode = createNode(data);
    
    // If the list is empty, the new node becomes the head
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    
    // Otherwise, traverse to the last node
    Node* last = *headRef;
    while (last->next != NULL) {
        last = last->next;
    }
    
    // Link the new node to the end
    last->next = newNode;
}

/**
 * reverseList: Reverses a singly linked list in-place.
 * It uses three pointers: prev, current, and next_node.
 * @param headRef A pointer to the head pointer of the list.
 *                The head pointer will be updated to point to the new head (the old tail).
 */
void reverseList(Node** headRef) {
    Node* prev = NULL;
    Node* current = *headRef;
    Node* next_node = NULL;

    // Traverse the list and reverse the links
    while (current != NULL) {
        // Store the next node before breaking the link
        next_node = current->next;
        
        // Reverse the 'next' pointer of the current node
        current->next = prev;
        
        // Move the pointers one position forward
        prev = current;
        current = next_node;
    }
    
    // After the loop, 'prev' points to the new head of the reversed list
    *headRef = prev;
}

/**
 * printList: Prints the elements of the linked list.
 * @param head A pointer to the first node of the list.
 */
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

/**
 * freeList: Deallocates all nodes in the list to prevent memory leaks.
 * @param headRef A pointer to the head pointer of the list.
 *                The head is set to NULL after freeing all nodes.
 */
void freeList(Node** headRef) {
    Node* current = *headRef;
    Node* temp;
    
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    
    // Set the original head pointer to NULL to avoid dangling pointers
    *headRef = NULL;
}
