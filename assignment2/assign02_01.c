#include<stdio.h>

void AddnewBook(int isbns[], int quantities[], char titles[][50], float prices[], int* bookcount)
{
    int bookcode;   //bookcode stores isbn.....
    printf("\nEnter a new ISBN: ");   
    scanf("%d",&bookcode);

    int i=0;          //counter for loop  
    for(int i=0; i<*bookcount; i++) 
    {
        if(isbns[i] == bookcode)   //checks the first isbn with the array of isbns at position '0'
        {
            printf("\nThis book already exists.");
            return;
        }
    }
    isbns[*bookcount]=bookcode;      //stores the first isbn in the array isbns at a position that would correspond with other arrays
    printf("Enter Book Title: ");   
    scanf(" %[^\n]",titles[*bookcount]);         //stores string........'\n' removed
    printf("Enter Book Price: ");
    scanf("%f",&prices[*bookcount]);
    printf("Enter Book Quantity: ");
    scanf("%d",&quantities[*bookcount]);   
    printf("Book added successfully!\n");
    printf("\n------------------------------------------------------------------");
    (*bookcount)++; 

    if (*bookcount>=100) 
    {
        printf("No new books can be added.");
        return;
    }
}

void ProcessSale(int isbns[], int quantities[], int bookcount)
{
    int bookcode, number;
    printf("\nEnter ISBN of a book to be sold: ");
    scanf("%d",&bookcode);
    printf("Enter the quantity to be sold: ");
    scanf("%d",&number);

    int available=0;
    for(int i=0; i<bookcount; i++) 
    {
        if(isbns[i]==bookcode) //if book in  the array
        {
            available=1;
            if(quantities[i]>=number) 
            {
                quantities[i]-=number;     //remaining
                printf("\nSale processed successfully. Book copies remaining: %d", quantities[i]);
                printf("\n------------------------------------------------------------------");
            } 
            else 
            {
                printf("\nNot enough stock, only %d copies available.", quantities[i]);
                printf("\n------------------------------------------------------------------");
            }
            break;
        }
    }

    if(!available) 
    {
        printf("\nBook not found.");
        printf("\n------------------------------------------------------------------");
    }
}

void GenerateReport(int isbns[], int quantities[], char titles[][50], float prices[], int bookcount)
{
    printf("\n===Low Stock Report===\n"); 
    int availability=0, i=0; 
    for(i=0; i<bookcount; i++) 
    { 
        if(quantities[i]<5) 
        { 
            availability=1; 
            printf("\nISBN: %d\nBook Title: %s\nPrice: %.2f\nQuantity: %d",isbns[i],titles[i],prices[i],quantities[i]); 
            printf("\n------------------------------------------------------------------");
        } 
    } 

    if(!availability) 
    { 
        printf("\nAll books are sufficiently stocked."); 
        printf("\n------------------------------------------------------------------");
    }
}

int main()
{
    int isbns[100], quantities[100], choice, bookcount=0;
    char titles[100][50];
    float prices[100];
    printf("\n===Liberty Books===\n");
    printf("==MENUE==\n");
    printf("1. Add New Book\n2. Process a Sale\n3. Generate Low-Stock Report\n");
    printf("------------------------------------------------------------------\n");
    do
    {
        printf("\n\nInput selection: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                AddnewBook(isbns, quantities, titles, prices, &bookcount); //func call
                break;
            case 2:
                ProcessSale(isbns, quantities, bookcount);    //func call
                break;
            case 3:
                GenerateReport(isbns, quantities, titles, prices, bookcount);     //func call
                break;
            default:
                break;
        }
    } 
    while (choice>=1 && choice<=3);
    return 0;
}