#include <stdio.h>
#include <stdlib.h>

/* Simple singly-linked list node */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* Create a new node holding 'value'. Returns pointer or exits on failure. */
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

/* Append a node with 'value' at the end of the list.
   head_ref is pointer to the head pointer so we can update it if list is empty. */
void append_node(Node **head_ref, int value) {
    Node *new_node = create_node(value);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node *cur = *head_ref;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = new_node;
}

/* Reverse the list in-place and return the new head pointer. */
Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *cur = head;
    while (cur != NULL) {
        Node *next = cur->next;  /* save next */
        cur->next = prev;        /* reverse pointer */
        prev = cur;              /* move prev forward */
        cur = next;              /* move cur forward */
    }
    return prev; /* prev is the new head */
}

/* Print the list values on one line separated by spaces. */
void print_list(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) printf(" ");
        cur = cur->next;
    }
    printf("\n");
}

/* Free all nodes in the list to avoid memory leaks. */
void free_list(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
}

int main(void) {
    Node *head = NULL;
    int n, value;

    printf("How many integers will you enter? ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Exiting.\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        printf("No numbers to read. Exiting.\n");
        return EXIT_SUCCESS;
    }

    printf("Enter %d integers (separated by spaces or newlines):\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Failed to read integer #%d. Exiting.\n", i + 1);
            free_list(head);
            return EXIT_FAILURE;
        }
        append_node(&head, value);
    }

    printf("\nOriginal list:\n");
    print_list(head);

    head = reverse_list(head);

    printf("Reversed list:\n");
    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}

