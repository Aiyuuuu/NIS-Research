/* singly_linked_reverse.c
 *
 * Build a singly linked list from integers read from stdin (one or more per line),
 * appending each number to the tail. Then reverse the list and print its elements.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o singly_linked_reverse singly_linked_reverse.c
 *
 * Usage:
 *   ./singly_linked_reverse
 *   (then type integers, e.g. "1 2 3 4", or feed a file: ./singly_linked_reverse < numbers.txt)
 */

#include <stdio.h>
#include <stdlib.h>

/* Node for singly linked list */
typedef struct Node {
    int value;
    struct Node *next;
} Node;

/* Append a new node with 'val' to the tail.
 * Maintains head and tail pointers; both are pointers to pointers so they can be updated.
 */
int append_tail(Node **headp, Node **tailp, int val) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) return 0; /* failure */
    n->value = val;
    n->next = NULL;
    if (*tailp != NULL) {
        (*tailp)->next = n;
        *tailp = n;
    } else {
        /* empty list */
        *headp = *tailp = n;
    }
    return 1; /* success */
}

/* Reverse the singly linked list iteratively. Returns new head. */
Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

/* Print list values separated by spaces, then newline. */
void print_list(Node *head) {
    Node *p = head;
    int first = 1;
    while (p != NULL) {
        if (!first) putchar(' ');
        first = 0;
        /* Use printf to print each integer */
        printf("%d", p->value);
        p = p->next;
    }
    putchar('\n');
}

/* Free all nodes in the list. */
void free_list(Node *head) {
    Node *p = head;
    while (p != NULL) {
        Node *next = p->next;
        free(p);
        p = next;
    }
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int x;

    /* Read integers from stdin until EOF. */
    while (scanf("%d", &x) == 1) {
        if (!append_tail(&head, &tail, x)) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    /* Reverse the list */
    head = reverse_list(head);

    /* Print all elements of the reversed list */
    print_list(head);

    /* Clean up memory */
    free_list(head);

    return EXIT_SUCCESS;
}

