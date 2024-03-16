#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

void printNumbers(const int arr[], int n) { // Function to print the elements of an array


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
// This function finds all the "leaders" in an integer array. A leader is an element that is greater than all the elements to its right.
void findLeaders(const int arr[], int n, int leadersArr[], int *sp) {

    //this is for the part if our array is empty
    if(n<=0){
      return;
    }

int l;
int counter = 0; // counter for number of leaders found

int maximum = arr[n-1]; // assume the rightmost element is a leader
leadersArr[counter] = maximum;
counter++;

// goes through right to left
for (l = n-2; l >= 0; l--) {

    if (arr[l] >= maximum) {  // check if the current element is greater or equal to its right hand side
        maximum = arr[l]; // update the max
        leadersArr[counter] = maximum; // add the new element to our Leaders Array
        counter++;
    }
}

*sp = counter; // store the number of leaders that been found
}

int main() {
    int arr[SIZE];
    int n;
    int leadersArr[SIZE];
    int s;
    readInput(arr, &n);
    printf("Array elements: ");
    printNumbers(arr, n);
    findLeaders(arr, n, leadersArr, &s);
    printf("Leaders Array elements: ");
    printNumbers(leadersArr, s); // changed this line to print leadersArr instead of arr
    return 0;
}

