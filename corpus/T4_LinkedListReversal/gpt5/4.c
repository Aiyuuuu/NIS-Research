// reverse_list.c
// Build a singly linked list by appending input integers at the tail,
// reverse the list in-place, and print the result.
//
// Compile:
//   gcc -std=c11 -Wall -Wextra -O2 reverse_list.c -o reverse_list
//
// Usage examples:
//   echo "1 2 3 4 5" | ./reverse_list
//   ./reverse_list < numbers.txt

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

/* Append value at tail. Uses pointer-to-pointer for head and a tail pointer for O(1) appends. */
void append_tail(Node **head_ref, Node **tail_ref, int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->val = value;
    node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = node;
        *tail_ref = node;
    } else {
        (*tail_ref)->next = node;
        *tail_ref = node;
    }
}

/* Reverse singly linked list in-place and return new head. */
Node* reverseList(Node *head) {
    Node *prev = NULL;
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next; // save next
        curr->next = prev;       // reverse pointer
        prev = curr;             // move prev forward
        curr = next;             // move curr forward
    }
    return prev; // new head
}

/* Print list values separated by spaces, followed by newline. */
void print_list(Node *head) {
    Node *p = head;
    int first = 1;
    while (p != NULL) {
        if (!first) putchar(' ');
        first = 0;
        printf("%d", p->val);
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

    /* Read all integers from stdin until EOF. */
    while (scanf("%d", &x) == 1) {
        append_tail(&head, &tail, x);
    }

    /* If no input, print nothing (just exit cleanly). */
    if (head == NULL) {
        return 0;
    }

    /* Reverse the list in-place. */
    head = reverseList(head);

    /* Print the reversed list. */
    print_list(head);

    free_list(head);
    return 0;
}

