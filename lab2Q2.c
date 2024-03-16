#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

    //as you mention i used the same readInput and printNumbers methods as i write in the first part of the lab

void readInput(int arr[], int *nPtr) { // Function to read input from user and store it in an array

    printf("Enter the number of elements:\n"); // Prompt the user to enter the number of elements
    int n;
    scanf("%d", &n); // Read number of elements entered by the user
    *nPtr = n; // Store the number of elements in the memory cell pointed to by nPtr

    printf("Enter %d elements:\n", n); // Prompt the user to enter the elements

    for (int k = 0; k < n; k++) {
        scanf("%d", &arr[k]); // Read each element and store it in arr
    }
}

void printNumbers(const int arr[], int n) { // Function to print the elements of an array

    printf("Array elements: ");
    for (int k = 0; k < n; k++) {
        printf("%d ", arr[k]); // Print each element in arr
    }
    printf("\n"); // Print a newline character at the end
}

// Finds the minimum and maximum elements of an integer array.

void findMinMax(const int arr[], int n, int *minPtr, int *maxPtr)
{
    if (n == 0) {
        // empty array, so there is no minimum or maximum
        return;
    }

    // initialize min and max to first element of the array
    *minPtr = *maxPtr = arr[0];

    // loop through the rest of the array to find the minimum and maximum
    for (int k = 1; k < n; k++) {
        if (arr[k] < *minPtr) {
            // found a new minimum value, so update minPtr
            *minPtr = arr[k];
        }
        if (arr[k] > *maxPtr) {
            // found a new maximum value, so update maxPtr
            *maxPtr = arr[k];
        }
    }
}

int main() {
        int arr[SIZE];
        int n, min, max;

        readInput(arr, &n);
        printNumbers(arr, n);
		findMinMax(arr, n, &min, &max);
		printf("Minimum of array is: %d", min);
		printf("\nMaximum of array is: %d", max);
        return 0;
}
