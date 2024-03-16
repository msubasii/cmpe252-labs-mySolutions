#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int id; // researcher id
    char name[20]; // researcher name
	char surname[20]; // researcher surname
    char department[20]; // department of researcher
    int citIndex; // citation index of the researcher
} researcher;

void showRecords(FILE *filePtr);

int modifyCitIndex(FILE *filePtr, unsigned int id, int increaseCit);
int insertResearcher(FILE *filePtr, unsigned int id, char name[], char surname[], char department[], int citIndex);
int removeResearcher(FILE *filePtr, unsigned int id);
int viewDepartmentCits(FILE *filePtr, char department[], int maxCit);

int main()
{
    unsigned int id;
    int increaseCit;
    int status;

    char name[20];
    char surname[20];
	char department[20];
    int citIndex;

    int count;
	int maxCitation;

    FILE *filePtr;
    filePtr = fopen("researcher.bin","rb+");
    if (filePtr == NULL)
    {
        printf("Could not open researcher.bin");
        return;
    }

    showRecords(filePtr);

    int choice;

    printf("\nWhich operation do you choose?\n");
    printf("1 : Update Citation Index\n");
    printf("2 : Add Researcher\n");
    printf("3 : Delete researcher\n");
    printf("4 : View Department Info with Citation\n");
    printf("> ");
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
        printf("\nResearcher id: ");
        scanf("%d",&id);
        printf("Increase value for citation index: ");
        scanf("%d",&increaseCit);
        status = modifyCitIndex(filePtr, id, increaseCit);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No researcher with id %d\n", id);
        break;
    case 2:
        printf("\nResearcher id: ");
        scanf("%d",&id);
        printf("Name: ");
        scanf("%s",name);
		printf("Surname: ");
        scanf("%s",surname);
        printf("Department: ");
        scanf("%s",department);
        printf("Citation Index: ");
        scanf("%d",&citIndex);
        status = insertResearcher(filePtr, id, name, surname, department, citIndex);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("There is already an researcher with id %d\n", id);
        break;
    case 3:
        printf("\nResearcher id: ");
        scanf("%d",&id);
        status = removeResearcher(filePtr, id);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No researcher with id %d\n", id);
        break;
    case 4:
        printf("\nDepartment: ");
        scanf("%s",department);
		printf("\nMax Citation Index: ");
        scanf("%d",maxCitation);
        count = viewDepartmentCits(filePtr, department, maxCitation);
        if (count == 0)
            printf("No researcher in department %s with citation index <= %d\n", department, maxCitation);
        else
            printf("There are %d researchers in department %s with citation index <= %d\n", count, department, maxCitation);
        break;
    }

    fclose(filePtr);
    return 0;
}

void showRecords(FILE *filePtr)
{
    fseek(filePtr, 0, SEEK_SET);

    printf("\n%-3s %-20s %-20s %-20s %s\n",
                   "ID",
                   "Name",
				   "Surname",
                   "Department",
                   "Citation Index");

    while (!feof(filePtr))
    {
        researcher r;
        int result = fread(&r, sizeof(researcher), 1, filePtr);
        if (result != 0 && r.id != 0)
        {
            printf("%-3d %-20s %-20s %-20s %d\n",
                   r.id,
                   r.name,
				   r.surname,
                   r.department,
                   r.citIndex);
        }
    }
}

int modifyCitIndex(FILE *filePtr, unsigned int id, int increaseCit)
{
    fseek(filePtr, (id - 1) * sizeof(researcher), SEEK_SET);

    researcher r;
    int result = fread(&r, sizeof(researcher), 1, filePtr);
    if (result != 0 && r.id != 0)
    {
        r.citIndex += increaseCit;
        fseek(filePtr, -sizeof(researcher), SEEK_CUR);
        fwrite(&r, sizeof(researcher), 1, filePtr);
        return 1;
    }

    return 0;
}

int insertResearcher(FILE *filePtr, unsigned int id, char name[], char surname[], char department[], int citIndex)
{
    fseek(filePtr, (id - 1) * sizeof(researcher), SEEK_SET);

    researcher r;
    int result = fread(&r, sizeof(researcher), 1, filePtr);
    if (result != 0 && r.id != 0)
    {
        return 0; // A researcher with the same ID already exists
    }

    r.id = id;
    strcpy(r.name, name);
    strcpy(r.surname, surname);
    strcpy(r.department, department);
    r.citIndex = citIndex;

    fseek(filePtr, (id - 1) * sizeof(researcher), SEEK_SET);
    fwrite(&r, sizeof(researcher), 1, filePtr);

    return 1;
}

int removeResearcher(FILE *filePtr, unsigned int id)
{
    fseek(filePtr, (id - 1) * sizeof(researcher), SEEK_SET);

    researcher r;
    int result = fread(&r, sizeof(researcher), 1, filePtr);
    if (result != 0 && r.id != 0)
    {
        r.id = 0; // Mark the record as deleted
        strcpy(r.name, "");
        strcpy(r.surname, "");
        strcpy(r.department, "");
        r.citIndex = 0;

        fseek(filePtr, -sizeof(researcher), SEEK_CUR);
        fwrite(&r, sizeof(researcher), 1, filePtr);
        return 1;
    }

    return 0;
}

int viewDepartmentCits(FILE *filePtr, char department[], int maxCit)
{
    int count = 0;

    fseek(filePtr, 0, SEEK_SET);

    while (!feof(filePtr))
    {
        researcher r;
        int result = fread(&r, sizeof(researcher), 1, filePtr);
        if (result != 0 && r.id != 0 && strcmp(r.department, department) == 0 && r.citIndex <= maxCit)
        {
            printf("%-3d %-20s %-20s %-20s %d\n",
                   r.id,
                   r.name,
                   r.surname,
                   r.department,
                   r.citIndex);
            count++;
        }
    }

    return count;
}
