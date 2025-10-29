#include <stdio.h>
#include <stdlib.h>

/* Singly linked list node */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* Create a new node with the given value (exits on allocation failure). */
Node *create_node(int value) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    n->data = value;
    n->next = NULL;
    return n;
}

/* Append a value to the end of the list. Maintains head and tail pointers. */
void append_node(Node **head, Node **tail, int value) {
    Node *n = create_node(value);
    if (*head == NULL) {
        *head = *tail = n;
    } else {
        (*tail)->next = n;
        *tail = n;
    }
}

/* Reverse the singly linked list in-place and return the new head. */
Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;

    while (curr != NULL) {
        next = curr->next;   /* save next node */
        curr->next = prev;   /* reverse pointer */
        prev = curr;         /* step prev forward */
        curr = next;         /* step curr forward */
    }
    return prev; /* prev is the new head */
}

/* Print list elements separated by spaces, ending with a newline. */
void print_list(const Node *head) {
    const Node *p = head;
    while (p != NULL) {
        printf("%d", p->data);
        if (p->next != NULL) putchar(' ');
        p = p->next;
    }
    putchar('\n');
}

/* Free all nodes in the list. */
void free_list(Node *head) {
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int value;

    printf("Enter integers separated by spaces or newlines (EOF to finish):\n");

    /* Read integers from standard input until EOF or non-integer input. */
    while (scanf("%d", &value) == 1) {
        append_node(&head, &tail, value);
    }

    if (head == NULL) {
        printf("No integers were provided. Exiting.\n");
        return 0;
    }

    printf("Original list: ");
    print_list(head);

    head = reverse_list(head);

    printf("Reversed list: ");
    print_list(head);

    free_list(head);
    return 0;
}

