#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>     //error.h  equivalent to  errno.h

void insertLine(char **lines[], int *count, int *capacity, int index, const char *text) 
{
    if (index < 0 || index > *count) {
        printf("Invalid index!\n");
        return;
    }

    // Grow array if needed
    if (*count == *capacity) {
        *capacity = *capacity * 2;
        char **temp = realloc(*lines, (*capacity) * sizeof(char*));
        if (!temp) {
            perror("Realloc failed");
            exit(1);
        }
        *lines = temp;
    }

    // Shift pointers right
    memmove(&(*lines)[index + 1], &(*lines)[index],
            (*count - index) * sizeof(char*));

    // Allocate exact memory for new string
    (*lines)[index] = malloc(strlen(text) + 1);
    if (!(*lines)[index]) {
        perror("malloc failed");
        exit(1);
    }
    strcpy((*lines)[index], text);

    (*count)++;
}

void deleteLine(char ***lines, int *count, int index) 
{
    if (index < 0 || index >= *count) {
        printf("Invalid index!\n");
        return;
    }

    free((*lines)[index]);

    // Shift left
    memmove(&(*lines)[index], &(*lines)[index + 1],
            (*count - index - 1) * sizeof(char*));

    (*count)--;
}

void printAllLines(char **lines, int count) 
{
    printf("\n===== TEXT BUFFER =====\n");

    if (count == 0) {
        printf("[No lines]\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}

void saveToFile(char **lines, int count) 
{
    FILE *fp = fopen("output.txt", "w");
    if (!fp) {
        perror("File open failed");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", lines[i]);
    }

    fclose(fp);
    printf("Saved to output.txt\n");
}

void shrinkToFit(char ***lines, int *capacity, int count) 
{
    if (*capacity == count) {
        printf("Already perfect size.\n");
        return;
    }

    char **temp = realloc(*lines, count * sizeof(char*));
    if (!temp) {
        perror("Realloc failed");
        exit(1);
    }

    *lines = temp;
    *capacity = count;

    printf("Shrunk memory to %d lines.\n", count);
}

void freeAll(char ***lines, int *count) 
{
    for (int i = 0; i < *count; i++) {
        free((*lines)[i]);
    }

    free(*lines);
    *lines = NULL;
    *count = 0;
}

void loadFromFile(char ***lines, int *count, int *capacity) 
{
    FILE *fp = fopen("output.txt", "r");
    if (!fp) {
        perror("Cannot open file");
        return;
    }

    // Free old data
    freeAll(lines, count);

    int initialCapacity = 4;
    *capacity = initialCapacity;

    *lines = malloc((*capacity) * sizeof(char*));
    if (!*lines) {
        perror("malloc failed");
        exit(1);
    }

    int maxInputSize = 1000;
    char *buffer = malloc(maxInputSize);

    while (fgets(buffer, maxInputSize, fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertLine(lines, count, capacity, *count, buffer);
    }

    free(buffer);
    fclose(fp);

    printf("Loaded file successfully!\n");
}

int main()
{
    //initial space for 10
    int initialCapacity=10,Capacity;

    //dyn. charac. array created
    char** textEditor=(char**)malloc(initialCapacity*sizeof(char*));
    //if this array fails....
    if (textEditor==NULL) 
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int count=0;    //lines user typed
    Capacity=initialCapacity;    //occupied space by array

    //buffer -> DMA that stores a line typed by user before saving it permanently
    char *buffer=malloc(Capacity);
    //if buffer array fails....
    if (buffer==NULL) 
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int choice,index;
    while (1) //infinite loop
    {
        printf("\n==== TEXT EDITOR MENU ====\n");
        printf("1. Insert new line\n2. Delete a line\n3. Print all lines\n4. Shrink to fit\n5. Save to file\n6. Load from file\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        while (getchar()!='\n');

        if (choice==1)
        {
            //User chooses where to insert line
            printf("Enter index to insert at: ");
            scanf("%d",&index);
            while(getchar()!='\n'); //removes extra '\n'
            printf("Enter text: ");
            fgets(buffer,Capacity,stdin);     //input text
            buffer[strcspn(buffer,"\n")]='\0';       //'\n' rmeoved -> null terminator added at the end fo the line 
            //function call for adding line 
            insertLine(&textEditor,&count,&initialCapacity,index,buffer);       
        }

        else if (choice==2) 
        {
            //User chooses which line to be dltd
            printf("Enter index to delete: ");
            scanf("%d",&index);
            //fucntion for dlting line called
            deleteLine(&textEditor,&count,index);
        }

        else if (choice==3) 
        {
            //prnt func. call
            printAllLines(textEditor,count);
        }
        else if (choice==4) 
        {
            //shrink feature for optimization
            shrinkToFit(&textEditor,&initialCapacity,count);
        }
        else if (choice == 5) 
        {
            saveToFile(textEditor,count);
        }
        else if (choice == 6) 
        {
            loadFromFile(&textEditor,&count,&initialCapacity);
        }
        else if (choice == 7) 
        {
            //free space used
            freeAll(&textEditor,&count);
            free(buffer);
            break;
        }
        else
            printf("Invalid choice.\n");
    }
    return 0;
}