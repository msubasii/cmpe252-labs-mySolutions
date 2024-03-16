#include <stdio.h>

#define SIZE 1000 // Define a constant macro named SIZE with the value 1000



void printNumbers(const int arr[], int n) { // Function to print the elements of an array

    printf("Array elements: ");
    for (int k = 0; k < n; k++) {
        printf("%d ", arr[k]); // Print each element in arr
    }
    printf("\n"); // Print a newline character at the end
}


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

int main() {
    int n; // Declare an integer variable n
    int arr[SIZE]; // Declare an integer array with the size SIZE
    readInput(arr, &n); // Call readInput function to read input from user and store it in arr and n
    printNumbers(arr, n); // Call printNumbers function to print the elements of arr
    return 0; // Exit the program
}
