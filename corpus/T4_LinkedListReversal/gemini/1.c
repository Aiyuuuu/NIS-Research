/**
 * @file singly_linked_list_reverse.c
 * @brief A C program to create, reverse, and print a singly linked list of integers.
 * @author Expert C Programmer
 *
 * This program demonstrates the fundamental operations on a singly linked list:
 * 1. Node Creation: Dynamically allocating memory for a new node.
 * 2. Insertion at Tail: Efficiently adding new elements to the end of the list (O(1)).
 * 3. Reversal: In-place reversal of the list using an iterative three-pointer approach (O(n)).
 * 4. Traversal/Printing: Displaying the list's contents.
 * 5. Memory Management: Properly freeing all allocated memory to prevent leaks.
 *
 * The program reads an arbitrary number of integers from standard input until
 * non-integer input or EOF is encountered.
 *
 * How to compile and run:
 *   gcc -Wall -Wextra -std=c11 -o singly_linked_list_reverse singly_linked_list_reverse.c
 *   ./singly_linked_list_reverse
 *
 * Example usage:
 *   Enter integers separated by spaces (e.g., 10 20 30 40), then press Enter
 *   and either a non-numeric character (like 'q') and Enter, or Ctrl+D (on Linux/macOS)
 *   or Ctrl+Z then Enter (on Windows) to signal end of input.
 *
 *   Input: 1 8 3 5 9
 *   Output:
 *   Original list: 1 -> 8 -> 3 -> 5 -> 9 -> NULL
 *   Reversed list: 9 -> 5 -> 3 -> 8 -> 1 -> NULL
 */

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the singly linked list.
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function Prototypes
Node* create_node(int data);
void add_to_tail(Node** head, Node** tail, int data);
void reverse_list(Node** head);
void print_list(Node* head);
void free_list(Node** head);

/**
 * @brief The main function to drive the program.
 */
int main(void) {
    // Pointers to the head and tail of the list.
    // Using a tail pointer allows for O(1) insertion at the end.
    Node* head = NULL;
    Node* tail = NULL;
    int value;

    printf("Enter integers (press non-integer or EOF to stop):\n");

    // Read integers from stdin until scanf fails (e.g., non-numeric input or EOF).
    while (scanf("%d", &value) == 1) {
        add_to_tail(&head, &tail, value);
    }

    printf("\nOriginal list: ");
    print_list(head);

    // Reverse the linked list in-place.
    reverse_list(&head);

    printf("Reversed list: ");
    print_list(head);

    // Free all dynamically allocated memory.
    free_list(&head);

    return 0;
}

/**
 * @brief Creates a new list node and initializes it.
 * @param data The integer value to store in the node.
 * @return A pointer to the newly allocated and initialized node.
 *         Exits the program if memory allocation fails.
 */
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/**
 * @brief Adds a new node with the given data to the tail of the list.
 * @param head A pointer to the head pointer of the list.
 * @param tail A pointer to the tail pointer of the list.
 * @param data The integer value for the new node.
 */
void add_to_tail(Node** head, Node** tail, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        // If the list is empty, the new node is both head and tail.
        *head = new_node;
        *tail = new_node;
    } else {
        // Otherwise, link the current tail to the new node and update the tail.
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

/**
 * @brief Reverses a singly linked list in-place.
 * @param head A pointer to the head pointer of the list. After the function
 *             returns, this pointer will point to the new head of the
 *             reversed list.
 */
void reverse_list(Node** head) {
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;

    // A list is empty or has one node, it's already "reversed".
    if (current == NULL || current->next == NULL) {
        return;
    }

    while (current != NULL) {
        // 1. Store the next node before we break the link.
        next = current->next;
        
        // 2. Reverse the 'next' pointer of the current node to point to the previous one.
        current->next = prev;
        
        // 3. Move the pointers one position ahead for the next iteration.
        prev = current;
        current = next;
    }
    
    // 4. After the loop, `prev` points to the last node of the original list,
    //    which is the new head of the reversed list.
    *head = prev;
}

/**
 * @brief Traverses the list and prints its elements.
 * @param head A pointer to the head of the list.
 */
void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

/**
 * @brief Frees all memory allocated for the list nodes.
 * @param head A pointer to the head pointer of the list. It sets the head to NULL
 *             after freeing to prevent use of a dangling pointer.
 */
void free_list(Node** head) {
    Node* current = *head;
    Node* next_node;

    while (current != NULL) {
        next_node = current->next; // Save the next node
        free(current);             // Free the current node
        current = next_node;       // Move to the next node
    }
    
    // Set the original head pointer to NULL to indicate the list is now empty.
    *head = NULL;
}
