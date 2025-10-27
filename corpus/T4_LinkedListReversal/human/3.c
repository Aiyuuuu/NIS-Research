/*
	Reversing a linked list in-place, written in C

	BSD 2-Clause License

	Copyright (c) 2019, Daniel Lorch
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>

/* 
 * Function prototypes (from the old .h file)
 */
typedef struct _linked_list {
    struct _linked_list* next;
    int value;
} linked_list;

void print_linked_list(linked_list* list);
linked_list* make_linked_list(int value);
void destroy_linked_list(linked_list** list);
void reverse_linked_list(linked_list** list);
void fatal_error(char* msg);
void append(linked_list* list, int value);

void fatal_error(char* msg) {
    fprintf(stderr, "%s", msg);
    exit(1);
}

void print_linked_list(linked_list* list) {
    linked_list* current = list;

    while(current != (linked_list*)NULL) {
        if(current->next != (linked_list*)NULL) {
            printf("%d, ", current->value);
        } else {
            printf("%d", current->value);
        }
        current = current->next;
    }

    printf("\n");
}

linked_list* make_linked_list(int value) {
    linked_list* list = malloc(sizeof(linked_list));

    if(list == (linked_list*)NULL) {
        fatal_error("malloc failed\n");
    }

    list->next = (linked_list*)NULL;
    list->value = value;

    return list;
}

void append(linked_list* list, int value) {
    linked_list* last = list;

    // fast-forward to last element
    while(last->next != (linked_list*)NULL) {
        last = last->next;
    }

    last->next = make_linked_list(value);
}

void destroy_linked_list(linked_list** list) {
    linked_list* current = *list;
    linked_list* next;

    while(current != (linked_list*)NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *list = (linked_list*)NULL;
}

// reverse a linked list in-place
void reverse_linked_list(linked_list** list) {
    linked_list* current = *list;
    linked_list* next = (linked_list*)NULL;
    linked_list* prev = (linked_list*)NULL;

    while(current != (linked_list*)NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *list = prev;
}

int main() {
    linked_list* list = NULL;
    int value;
    linked_list* temp = NULL;

    printf("Enter integers (Ctrl+D to end):\n");

    if (scanf("%d", &value) != 1) {
        printf("No input provided.\n");
        return 0;
    }

    list = make_linked_list(value);

    while (scanf("%d", &value) == 1) {
        append(list, value);
    }

    print_linked_list(list);

    reverse_linked_list(&list);
    print_linked_list(list);

    destroy_linked_list(&list);

    return 0;
}

