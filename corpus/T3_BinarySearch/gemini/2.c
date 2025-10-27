#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Performs a binary search on a sorted integer array.
 * 
 * @param arr The sorted array to search in.
 * @param left The starting index of the search space.
 * @param right The ending index of the search space.
 * @param target The integer value to search for.
 * @return The index of the target if found, otherwise -1.
 */
int binarySearch(int arr[], int left, int right, int target) {
    // Loop until the search space is exhausted (left pointer crosses right pointer)
    while (left <= right) {
        // Calculate the middle index to avoid potential overflow
        // (left + right) / 2 can overflow if left and right are large
        int mid = left + (right - left) / 2;

        // Check if the target is present at the middle index
        if (arr[mid] == target) {
            return mid; // Target found
        }

        // If the target is greater, it must be in the right half.
        // Ignore the left half.
        if (arr[mid] < target) {
            left = mid + 1;
        }
        // If the target is smaller, it must be in the left half.
        // Ignore the right half.
        else {
            right = mid - 1;
        }
    }

    // If the loop finishes, the element was not present in the array
    return -1;
}

int main() {
    int n, i, target, result;
    int *arr;

    // 1. Read the number of elements
    printf("Enter the number of elements in the sorted list: ");
    scanf("%d", &n);

    // Defensive check for a valid count
    if (n <= 0) {
        printf("Invalid number of elements.\n");
        return 1;
    }

    // 2. Allocate memory for the array dynamically
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1; // Exit with an error code
    }

    // 3. Read the sorted list of numbers from the user
    printf("Enter %d sorted integers (one per line):\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 4. Read the target value to search for
    printf("Enter the target value to search for: ");
    scanf("%d", &target);

    // 5. Perform the binary search
    // The initial search space is the entire array, from index 0 to n-1
    result = binarySearch(arr, 0, n - 1, target);

    // 6. Display the result
    if (result != -1) {
        printf("\nElement %d found at index: %d\n", target, result);
    } else {
        printf("\nElement %d not found in the array.\n", target);
    }

    // 7. Clean up the dynamically allocated memory
    free(arr);

    return 0; // Indicate successful execution
}
