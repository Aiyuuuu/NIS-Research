#include <stdio.h>
#include <stdlib.h>

/* Bubble sort in ascending order */
void bubble_sort(int *a, size_t n) {
    if (n < 2) return;
    for (size_t i = 0; i < n - 1; ++i) {
        int swapped = 0;
        for (size_t j = 0; j < n - 1 - i; ++j) {
            if (a[j] > a[j+1]) {
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break; /* already sorted */
    }
}

int main(void) {
    int value;
    size_t capacity = 16;
    size_t count = 0;
    int *arr = malloc(capacity * sizeof *arr);
    if (!arr) {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Read integers from stdin until EOF */
    while (scanf("%d", &value) == 1) {
        if (count == capacity) {
            size_t new_cap = capacity * 2;
            int *tmp = realloc(arr, new_cap * sizeof *tmp);
            if (!tmp) {
                free(arr);
                fprintf(stderr, "Reallocation failed\n");
                return EXIT_FAILURE;
            }
            arr = tmp;
            capacity = new_cap;
        }
        arr[count++] = value;
    }

    /* Sort using bubble sort */
    bubble_sort(arr, count);

    /* Print sorted list to stdout (space-separated, newline at end) */
    for (size_t i = 0; i < count; ++i) {
        if (i) putchar(' ');
        printf("%d", arr[i]);
    }
    if (count) putchar('\n');

    free(arr);
    return EXIT_SUCCESS;
}

