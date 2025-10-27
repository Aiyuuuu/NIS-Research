#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list.
// Each node contains an integer 'data' and a pointer 'next'
// to the next node in the sequence.
struct Node {
    int data;
    struct Node* next;
};

// --- Function Prototypes ---
// We declare the functions here so main() knows they exist.
struct Node* createNode(int data);
void insertAtEnd(struct Node** head_ref, int new_data);
void reverseList(struct Node** head_ref);
void printList(struct Node* node);
void freeList(struct Node** head_ref);


// --- The Main Program ---
int main() {
    // 'head' is a pointer to the first node of our list.
    // We start with an empty list, so we initialize it to NULL.
    struct Node* head = NULL;
    int number;

    printf("--- Linked List Reversal Program ---\n");
    printf("Enter a sequence of integers (type a letter to finish):\n");

    // Loop to read integers from the user.
    // scanf returns the number of items successfully read.
    // It will return 1 as long as we type an integer.
    // If we type a letter, it returns 0, and the loop stops.
    while (scanf("%d", &number) == 1) {
        insertAtEnd(&head, number);
    }

    // Print the original list to show what the user entered.
    printf("\nOriginal list: ");
    printList(head);

    // Reverse the list.
    printf("Reversing the list...\n");
    reverseList(&head);

    // Print the list again to show it in its new, reversed order.
    printf("Reversed list: ");
    printList(head);

    // It's very important to free the memory we allocated to prevent memory leaks.
    freeList(&head);
    printf("\nMemory has been freed.\n");

    return 0;
}


// --- Function Definitions ---

/**
 * @brief Allocates memory for a new node and initializes it.
 * @param data The integer value to store in the new node.
 * @return A pointer to the newly created node.
 */
struct Node* createNode(int data) {
    // Allocate memory for a new node using malloc.
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Always check if malloc was successful.
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1); // Exit the program if we can't get memory.
    }

    // Set the node's data and make its 'next' pointer NULL.
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Inserts a new node at the end of the linked list.
 * @param head_ref A pointer to the head pointer of the list. We use a double
 *                 pointer so we can modify the head pointer itself if the list is empty.
 * @param new_data The integer data for the new node.
 */
void insertAtEnd(struct Node** head_ref, int new_data) {
    // 1. Create the new node.
    struct Node* newNode = createNode(new_data);

    // 2. If the list is empty, the new node becomes the head.
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }

    // 3. If the list is not empty, find the last node.
    struct Node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }

    // 4. Link the last node to our new node.
    last->next = newNode;
}

/**
 * @brief Reverses the linked list.
 * @param head_ref A pointer to the head pointer of the list.
 */
void reverseList(struct Node** head_ref) {
    struct Node* prev = NULL;    // The previous node, starts as NULL.
    struct Node* current = *head_ref; // The current node, starts at the head.
    struct Node* next = NULL;    // The next node in the original list.

    // Traverse the list and reverse the pointers at each step.
    while (current != NULL) {
        // 1. Store the next node before we change anything.
        next = current->next;

        // 2. Reverse the 'next' pointer of the current node.
        //    It should now point to the 'prev' node.
        current->next = prev;

        // 3. Move our 'prev' and 'current' pointers one step forward.
        prev = current;
        current = next;
    }

    // 4. After the loop, 'prev' is pointing to the new head of the list.
    *head_ref = prev;
}

/**
 * @brief Prints the data of each node in the list.
 * @param node A pointer to the head of the list to be printed.
 */
void printList(struct Node* node) {
    if (node == NULL) {
        printf("The list is empty.\n");
        return;
    }
    // Traverse from the given node to the end of the list.
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n"); // Indicate the end of the list.
}

/**
 * @brief Frees all the memory allocated for the list nodes.
 * @param head_ref A pointer to the head pointer of the list.
 */
void freeList(struct Node** head_ref) {
    struct Node* current = *head_ref;
    struct Node* next;

    while (current != NULL) {
        next = current->next; // Save the next node.
        free(current);        // Free the current node.
        current = next;       // Move to the next node.
    }

    // Set the original head pointer to NULL to signify the list is now empty.
    *head_ref = NULL;
}
