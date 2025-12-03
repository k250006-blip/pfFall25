#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure no. 1
typedef struct{
    int studentID;
    char fullName[100],batch[20],membership[10],regDate[12],dob[12],interest[10];
} Student;

Student *db = NULL;
int dbCount = 0;
void loadDatabase(const char *filename) 
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;  
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    dbCount = size / sizeof(Student);
    if (dbCount > 0) 
    {
        db = (Student *) malloc(dbCount * sizeof(Student));
        fread(db, sizeof(Student), dbCount, fp);
    }
    fclose(fp);
}

void saveDatabase(const char *filename) 
{
    FILE *fp = fopen(filename, "wb");
    if (!fp) 
    {
        printf("Error: Cannot save database.\n");
        return;
    }
    fwrite(db, sizeof(Student), dbCount, fp);
    fclose(fp);
}

int existsID(int id) 
{
    for (int i = 0; i < dbCount; i++)
        if (db[i].studentID == id)
            return 1;
    return 0;
}

void addStudent(const char *filename) 
{
    Student s;
    printf("\nEnter Student ID: ");
    scanf("%d", &s.studentID);
    getchar();
    if (existsID(s.studentID)) 
    {
        printf("Error: Student ID already exists.\n");
        return;
    }
    printf("Enter Full Name: ");
    fgets(s.fullName, sizeof(s.fullName), stdin);
    s.fullName[strcspn(s.fullName, "\n")] = '\0';
    printf("Enter Batch (CS/SE/Cyber/AI): ");
    scanf("%s", s.batch);
    printf("Membership Type (IEEE/ACM): ");
    scanf("%s", s.membership);
    printf("Registration Date (YYYY-MM-DD): ");
    scanf("%s", s.regDate);
    printf("Date of Birth (YYYY-MM-DD): ");
    scanf("%s", s.dob);
    printf("Interest (IEEE/ACM/Both): ");
    scanf("%s", s.interest);
    db = (Student *) realloc(db, (dbCount + 1) * sizeof(Student));
    db[dbCount] = s;
    dbCount++;
    saveDatabase(filename);
    printf("Student Registered Successfully!\n");
}

void updateStudent(const char *filename) 
{
    int id;
    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < dbCount; i++) {
        if (db[i].studentID == id) 
        {
            printf("Update Batch: ");
            scanf("%s", db[i].batch);
            printf("Update Membership Type (IEEE/ACM): ");
            scanf("%s", db[i].membership);
            saveDatabase(filename);
            printf("Record Updated Successfully!\n");
            return;
        }
    }
    printf("Record not found.\n");
}

void deleteStudent(const char *filename) 
{
    int id, found = -1;
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < dbCount; i++) {
        if (db[i].studentID == id) 
        {
            found = i;
            break;
        }
    }
    if (found == -1) 
    {
        printf("Record not found.\n");
        return;
    }
    for (int i = found; i < dbCount - 1; i++)
        db[i] = db[i + 1];
    dbCount--;
    db = (Student *) realloc(db, dbCount * sizeof(Student));
    saveDatabase(filename);
    printf("Record Deleted Successfully!\n");
}

void viewAll() 
{
    if (dbCount == 0) 
    {
        printf("No records found.\n");
        return;
    }
    printf("\n--- All Student Records ---\n");
    for (int i = 0; i < dbCount; i++) {
        printf("\nID: %d\nName: %s\nBatch: %s\nMembership: %s\nReg Date: %s\nDOB: %s\nInterest: %s\n",db[i].studentID, db[i].fullName, db[i].batch,db[i].membership, db[i].regDate, db[i].dob, db[i].interest);
    }
}

void batchReport() 
{
    char batch[20], type[10];
    printf("\nEnter Batch (CS/SE/Cyber/AI): ");
    scanf("%s",batch);        //no '&'  -> already an address
    printf("Enter Membership Type Filter (IEEE/ACM/Both): ");
    scanf("%s",type);   //no '&'  -> already an address
    printf("\nBatch Report\n\n", batch, type);
    for (int i = 0; i < dbCount; i++) {
        if (strcmp(db[i].batch, batch) == 0 && (strcmp(type, "Both") == 0 || strcmp(db[i].membership, type) == 0))
        {
            printf("ID: %d | %s | %s\n",db[i].studentID, db[i].fullName, db[i].membership);
        }
    }
}

int main() 
{
    loadDatabase("members.dat");
    while (1) {
        int choice;
        printf("\n------MEMBERSHIP MANAGER------\n");
        printf("1. Register New Student\n2. Update Student Record\n3. Delete Student\n4. View All Students\n5. Batch-wise Report\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1: 
                addStudent("members.dat"); 
                break;
            case 2: 
                updateStudent("members.dat"); 
                break;
            case 3: 
                deleteStudent("members.dat"); 
                break;
            case 4: 
                viewAll(); 
                break;
            case 5: 
                batchReport(); 
                break;
            case 6: 
                saveDatabase("members.dat");
                printf("Exiting... Data saved.\n");
                free(db);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}