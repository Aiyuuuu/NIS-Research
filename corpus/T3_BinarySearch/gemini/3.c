#include <stdio.h>

// --- Function Prototype ---
// We declare the function here so main() knows it exists.
int binarySearch(int arr[], int size, int target);


// --- Main Function ---
// This is where the program execution begins.
int main() {
    int n; // To store the number of elements in the list
    int i; // A simple loop counter
    
    // 1. Get the size of the list from the user
    printf("Enter the number of elements in the sorted list: ");
    scanf("%d", &n);
    
    // Declare an array of the size provided by the user
    int arr[n];
    
    // 2. Get the sorted numbers from the user
    printf("Enter the %d sorted numbers one by one:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 3. Get the number to search for
    int target; // The number we want to find
    printf("Enter the number to search for: ");
    scanf("%d", &target);
    
    // 4. Call the binary search function and store the result
    int result_index = binarySearch(arr, n, target);
    
    // 5. Print the result
    if (result_index != -1) {
        // We add 1 to the index because array indices start at 0,
        // but human-readable positions start at 1.
        printf("Number %d found at position: %d\n", target, result_index + 1);
    } else {
        printf("Number %d not found in the list.\n", target);
    }
    
    return 0; // Indicate successful program execution
}


// --- Binary Search Function Definition ---
// This function performs the binary search algorithm.
// It takes the array, its size, and the target number as input.
// It returns the index of the target if found, otherwise it returns -1.
int binarySearch(int arr[], int size, int target) {
    int low = 0;             // The starting index of the search space
    int high = size - 1;     // The ending index of the search space
    
    // The loop continues as long as the search space is valid (low <= high)
    while (low <= high) {
        // Calculate the middle index.
        // Using `low + (high - low) / 2` is a good practice to prevent
        // potential overflow if low and high were very large numbers.
        int mid = low + (high - low) / 2;
        
        // Check if the middle element is our target
        if (arr[mid] == target) {
            return mid; // Found it! Return the index.
        }
        
        // If the target is smaller than the middle element,
        // it must be in the left half.
        if (target < arr[mid]) {
            high = mid - 1; // Narrow the search to the left half
        }
        // Otherwise, the target must be in the right half.
        else {
            low = mid + 1; // Narrow the search to the right half
        }
    }
    
    // If the loop finishes, it means the target was not in the list.
    return -1;
}
