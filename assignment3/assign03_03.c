#include<stdio.h>
#include<string.h>
//structure no. 1
typedef struct
{
    int EmployeeID;
    char name[20],designation[20];
    float salary;
}EmployeeInfo;  //employeeinfo is the datatype.

//funtion no. 1
//im using recursion for display
void displayEmployees(EmployeeInfo employee[], int loop, int n)
{
    if (loop==n)
    {
        printf("-----------------------------------------------------\n");
        return;
    }
    //table form
    printf("%5d %12s %14s %10.2f\n",employee[loop].EmployeeID,employee[loop].name,employee[loop].designation,employee[loop].salary);
    displayEmployees(employee,loop+1,n);
}

//function no. 2
//highest salary to evaluate seniority and bonuses.
void findHighestSalary(EmployeeInfo employee[], int n)
{
    int maximumSalary=0;
    float max=employee[0].salary;

    for (int i = 0; i < n; i++)
    {
        if (employee[i].salary>max)
        {
            max=employee[i].salary;
            maximumSalary=i;
        }
    }
    printf("%5d %12s %14s %10.2f\n",employee[maximumSalary].EmployeeID,employee[maximumSalary].name,employee[maximumSalary].designation,max);
}

//function no. 3
void searchEmployee(EmployeeInfo employee[], int n)
{
    int choice,ID;
    char Name[20];
    printf("Search Emplyee:\n1. By Employee ID\n2. By Name");
    do
    {
        printf("\nEnter Search choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter Employee ID: ");
            scanf("%d",&ID);
            printf("\nSearched Employee Record(s) wrt ID: \n");
            printf("-----------------------------------------------------\n");
            printf("%5s %8s %14s %10s\n","EmployeeID","Name","Designation","Salary");
            printf("-----------------------------------------------------\n");

            int found=0,matchedEmployee;
            for (int i = 0; i < n; i++)
            {
                if (employee[i].EmployeeID==ID)
                {
                    found=1;
                    matchedEmployee=i;
                    break;
                }
            }
            printf("%5d %12s %14s %10.2f\n",employee[matchedEmployee].EmployeeID,employee[matchedEmployee].name,employee[matchedEmployee].designation,employee[matchedEmployee].salary);
            break;

        case 2:
            printf("\nEnter Employee Name: ");
            scanf("%s", Name);  //no '&' bcs its alr a string
            while (getchar()!='\n');
            printf("\nSearched Employee Record(s) wrt Name: \n");
            printf("-----------------------------------------------------\n");
            printf("%5s %8s %14s %10s\n","EmployeeID","Name","Designation","Salary");
            printf("-----------------------------------------------------\n");

            int match=0,matchedname;
            for (int i = 0; i < n; i++)
            {
                if (strcmp(employee[i].name,Name)==0)
                {
                    match=1;
                    matchedname=i;
                    break;
                }
            }
            printf("%5d %12s %14s %10.2f\n",employee[matchedname].EmployeeID,employee[matchedname].name,employee[matchedname].designation,employee[matchedname].salary);
            break;
        default:
            break;
        }
    } while (!(choice==1 || choice==2));
}

//function no. 4
void bonus(EmployeeInfo employee[], int n)
{
    float Salary=50000;
    float Bonus;
    for (int i = 0; i < n; i++)
    {
        if (employee[i].salary<=Salary)
        {
            Bonus=employee[i].salary*0.1;
            employee[i].salary+=Bonus;
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%5d %12s %14s %10.2f\n",employee[i].EmployeeID,employee[i].name,employee[i].designation,employee[i].salary);
    }
}
int main()
{
    printf("\n----ABC Technologies---\n");
    EmployeeInfo employee[100];  //object made that basically stores info inna form of array...kinda
    int choice=0,n=0;
    printf("\n----MENU----\n1. Add Employee\n2. View Employee Records\n3. Highest Salary Employee\n4. Serach Employee\n5. Bonus Awarded Employees\n6. Exit");
    do
    {
        printf("\nEnter choice: ");
        scanf("%d",&choice);
        while (getchar()!='\n');

        switch (choice)
        {
        case 1:
            printf("\nEnter the number of employees working for ABC Technologies: ");
            scanf("%d",&n);
            for (int i = 0; i < n; i++)
            {
                printf("\nInformation for Employee %d: ",i+1);
                printf("\nEmployee ID: ");
                scanf("%d",&employee[i].EmployeeID);
                printf("Employee Name: ");
                scanf(" %s",&employee[i].name);
                while (getchar()!='\n');       
                printf("Employee Designation: ");
                scanf("%s",&employee[i].designation);
                while (getchar()!='\n'); 
                printf("Employee Salary: ");
                scanf("%f",&employee[i].salary);
            }
            break;
        case 2:
            //table form
            printf("\nEmployee Record(s): \n");
            printf("-----------------------------------------------------\n");
            printf("%5s %8s %14s %10s\n","EmployeeID","Name","Designation","Salary");
            printf("-----------------------------------------------------\n");

            displayEmployees(employee,0,n);
            break;
        case 3:
            printf("\nSorted Employee Record(s) wrt Salary: \n");
            printf("-----------------------------------------------------\n");
            printf("%5s %8s %14s %10s\n","EmployeeID","Name","Designation","Salary");
            printf("-----------------------------------------------------\n");

            findHighestSalary(employee,n);
            break;
        case 4:
            searchEmployee(employee,n);
            break;
        case 5:
            printf("\nEmployee Record(s) wrt Bonus Awarded Salary: \n");
            printf("-----------------------------------------------------\n");
            printf("%5s %8s %14s %10s\n","EmployeeID","Name","Designation","Salary");
            printf("-----------------------------------------------------\n");
            
            bonus(employee,n);
            break;
        case 6:
        default:
            break;
        }
    } while (choice!=6);
    return 0;   
}
