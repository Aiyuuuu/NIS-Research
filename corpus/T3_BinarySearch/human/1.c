/*
    Rodrigo Duarte Silva Luz - 2019003520
    Yasmin Karolyne Ancieto Carvalho - 2018010440
    Matheus de Souza - 2019005909
*/

// This program implements a binary search.
// In the binary search, you must check the element that is at position (left + right) / 2 
// and print that element during the search.

// The input is given as follows:
// n x0 x1 x2 ... x(n-1) e
// Where "n" is the number of elements in the list, x0 through x(n-1) are the elements of the list 
// (for convenience there is a blank space after the last element), 
// and "e" is the element we want to find in the list.

// At the end, the program should print the position where the element was found 
// or -1 if it is not in the list, followed by a newline (suggested to print with "%d\n").
// The program should return 0 at the end.

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int target);

int main()
{
    // number of elements in the list
    int n = 0;

    scanf("%d", &n);

    // elements of the list
    int arr[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // element we want to find in the list
    int target = 0;
    scanf("%d", &target);

    int result = binarySearch(arr, n, target);
    printf("%d\n", result);

    return 0;
}

int binarySearch(int arr[], int n, int target)
{
    int left, mid, right;
    left = 0;
    right = n - 1;
    while (left <= right)
    {
        mid = (left + right) / 2;
        printf("%d\n", arr[mid]); // print the element being checked
        if (target < arr[mid])
            right = mid - 1;
        else if (target > arr[mid])
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}

