#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 20
#define MAX_ELEM 10

void findDifference(char *group1[], char *group2[], int n1, int n2, char *diff[], int *diffCountPtr){
    int diffCount = 0;  // counter to keep track of the number of elements in the difference
    int foundMatch = 0; // flag to check if a match is found between a string in group1 and group2

    // iterate through all strings in group1
    for(int i=0; i<n1; i++){
        foundMatch = 0;  // reset the flag for each string in group1

        // iterate through all strings in group2 to compare with the current string in group1
        for(int j=0; j<n2; j++){
            // use strcmp to compare the strings
            if(strcmp(group1[i], group2[j]) == 0){
                foundMatch = 1;  // set the flag if a match is found
                break;
            }
        }

        // if no match is found, add the string in group1 to the difference array
        if(!foundMatch){
            diff[diffCount] = group1[i];
            diffCount++;
        }
    }

    // update the output parameter with the number of elements in the difference array
    *diffCountPtr = diffCount;
}


void printNameSurnameAge(char *diff[], int diffCount){

    for (int i = 0; i < diffCount; i++){
        char *Name = diff[i];
        char *firstName = strtok(Name, "_");
        char *lastName = strtok(NULL, "_");
        char *ageStr = strtok(NULL, "_");

        int age = atoi(ageStr);

        printf("%s %s %d\n", firstName, lastName, age);
    }
}


perl
Copy code
int main() {
    char list[MAX_ELEM][STR_LEN] = {"", "zoe_vin_32", "sam_loaf_22","jack_lang_12", "david_studi_17", "denzel_bale_65",
                                     "james_feldman_76", "james_alonso_30", "michael_rodriguez_23", "dustin_smith_51"};

    char *group1[MAX_ELEM];
    int n1;

    char *group2[MAX_ELEM];
    int n2;

    int i, ind;

    printf("Enter the number of elements in group1 (up to %d):\n", MAX_ELEM);
    if(scanf("%d", &n1) != 1 || n1 < 1 || n1 > MAX_ELEM) {
        printf("Error: invalid input for group1 size.\n");
        return 1;
    }

    printf("Enter the indices of the elements in group1 (up to %d):\n", n1);
    for (i = 0; i < n1; i++) {
        if(scanf("%d", &ind) != 1 || ind < 1 || ind >= MAX_ELEM) {
            printf("Error: invalid input for group1 index %d.\n", i+1);
            return 1;
        }
        group1[i] = list[ind];
    }

    printf("\nEnter the number of elements in group2 (up to %d):\n", MAX_ELEM);
    if(scanf("%d", &n2) != 1 || n2 < 1 || n2 > MAX_ELEM) {
        printf("Error: invalid input for group2 size.\n");
        return 1;
    }

    printf("Enter the indices of the elements in group2 (up to %d):\n", n2);
    for (i = 0; i < n2; i++) {
        if(scanf("%d", &ind) != 1 || ind < 1 || ind >= MAX_ELEM) {
            printf("Error: invalid input for group2 index %d.\n", i+1);
            return 1;
        }
        group2[i] = list[ind];
    }

    char *diff[MAX_ELEM];
    int diffCount;

    findDifference(group1, group2, n1, n2, diff, &diffCount);

    printf("\ngroup1:\n");
    for (int i = 0; i < n1; i++) {
        printf("%s\n", group1[i]);
    }

    printf("\ngroup2:\n");
    for (int i = 0; i < n2; i++) {
        printf("%s\n", group2[i]);
    }

    printf("\ndifference of group1 from group2:\n");
    for (int i = 0; i < diffCount; i++) {
        printf("%s\n", diff[i]);
    }

    printf("\nDo you want to print the difference in Name Surname Age format (1/0)? ");
    int response;

    if (scanf("%d", &response) != 1) {
        printf("Error: invalid input for response.\n");
        return 1;
    }

    if (response == 1) {
        printf("\ndifference of group1 from group2 in Name Surname Age format:\n");
        printNameSurnameAge(diff, diffCount);
    }

    return 0;
}
