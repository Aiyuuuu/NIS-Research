/* reverse_list.c
 * Read integers from stdin, append to tail of a singly linked list,
 * reverse the list, print the reversed list, then clean up.
 *
 * Compile:
 *   gcc -std=c11 -Wall -Wextra -O2 -o reverse_list reverse_list.c
 *
 * Usage:
 *   ./reverse_list
 *   (type integers separated by spaces or newlines; finish with Ctrl+D or Ctrl+Z)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* Print all elements of the list on one line. */
void print_list(const Node *head) {
    const Node *p = head;
    if (!p) {
        printf("(empty list)\n");
        return;
    }

    while (p) {
        printf("%d", p->data);
        if (p->next) putchar(' ');
        p = p->next;
    }
    putchar('\n');
}

/* Reverse singly linked list iteratively; return new head. */
Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head;
    while (curr) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

/* Free all nodes in the list. */
void free_list(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int value;
    size_t count = 0;

    printf("Enter integers (separated by spaces or newlines). End with EOF (Ctrl+D on Unix, Ctrl+Z then Enter on Windows):\n");

    /* Read ints until EOF or non-integer input. scanf returns 1 for a successful integer read. */
    while (scanf("%d", &value) == 1) {
        Node *n = malloc(sizeof(Node));
        if (!n) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
        n->data = value;
        n->next = NULL;

        if (!head) {           /* first node */
            head = tail = n;
        } else {               /* append to tail */
            tail->next = n;
            tail = n;
        }
        ++count;
    }

    if (count == 0) {
        printf("No integers were entered. Exiting.\n");
        /* Clear any leftover input if desired; but program will exit now. */
        return EXIT_SUCCESS;
    }

    printf("\nOriginal list (%zu elements):\n", count);
    print_list(head);

    head = reverse_list(head);

    printf("\nReversed list:\n");
    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}

