#include <stdio.h>
#include<string.h>

// function no. 1 
void customerinformation(char name[], int namelength, char cnic[], int cniclength)
{
    printf("\nInput Customer Name: ");
    fgets(name,namelength,stdin);
    name[strcspn(name,"\n")]='\0';

    printf("Input Customer CNIC: ");
    fgets(cnic,cniclength,stdin);
    cnic[strcspn(cnic,"\n")]='\0';
    printf("---------------------------------------------------------------------------------------");
    printf("\nName: %s",name);
    printf("\nCNIC: %s\n",cnic);
    printf("---------------------------------------------------------------------------------------\n");
}

// function no. 2
void displayinventory(int Productcode[], int codelen, int Quantity[], int quan_len, float Price[], int pricelen)
{
    printf("\n===Display Inventory===\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Product code\t|\tQuantity in stock\t|\t\tPrice\t\t|\n");
    printf("--------------------------------------------------------------------------------\n");
    int i=0;
    for (i = 0; i < codelen; i++)
    {
        printf("%2d\t\t|\t\t%d\t\t|\t\t%.0f\t\t|\n",Productcode[i],Quantity[i],Price[i]);
        printf("--------------------------------------------------------------------------------\n");
    }
}

// function no.3
void updateinventory(int Productcode[], int codelen, int *Quantity, int quan_len, float Price[], int pricelen)
{
    int code,quantity;
    printf("\n===Update inventory===\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Enter Product code for purchase: ");    //telling which products are we purchasing
    scanf("%d",&code);
    printf("Enter quantity purchase: ");          //and the quantity of the purchase
    scanf("%d",&quantity);

    printf("\n\n--------------------------------------------------------------------------------\n");
    printf("Product code\t|\tQuantity in stock\t|\t\tPrice\t\t|\n");   
    printf("--------------------------------------------------------------------------------\n");
    int i=0;      //loop counter
    int product=0;      //flag to check product availability
    for (i = 0; i < codelen; i++)
    {
        if(Productcode[i]==code)        //if code matches any of the products in the array
        {
            if (quantity<=Quantity[i])       //and if the entered quantity is less or equal to the actuall quantity of the product in the array 
            {
                product=1;  // then product found
                Quantity[i]-=quantity;   //and purchase quantity is subtracted from the original quantity

                //displaying updated version of the invetory.....subtracting the purchase quantity
                printf("%2d\t\t|\t\t%d\t\t|\t\t%.0f\t\t|\n",Productcode[i],Quantity[i],Price[i]);
                printf("--------------------------------------------------------------------------------\n");
            }
            else     //if purchase quantity greater than its availability
            {
                printf("\nNot enough stock for product\n");
                printf("--------------------------------------------------------------------------------\n");
            }
        }
        
    }
    if(!product)    //if product not found --> 0
        {
            printf("\nProduct does not exist\n");
            printf("--------------------------------------------------------------------------------\n");
        }
}

//function no.4
float additem(int Productcode[], int codelen, int Quantity[], int quan_len, float Price[], int pricelen, float *total)
{
    int code, quantity;
    printf("\n=== Add Item to Cart ===\n");        //inventory mien whatever we had, we r now adding to cart for purchase 
    
    while (1)      //while the codition is true.....
    {
        printf("Enter Product code to add to cart (0 to stop): ");
        scanf("%d",&code);

        if (code==0)  //'0' tells that we no longer want to add products
            break;

        int product = 0;
        for (int i = 0; i < codelen; i++)
        {
            if (Productcode[i]==code)    //if the code matches any of the elements in the array
            {
                product=1;          //mark flag as true....product available
                printf("Enter quantity: ");
                scanf("%d",&quantity);

                if (quantity<=Quantity[i])    //if the entered quantity is less or equal to the actuall quantity of the product in the array
                {
                    Quantity[i]-=quantity;             // subtract
                    *total+=Price[i]*quantity;

                    printf("Added %d of product %d to cart succesfully!!\n",quantity,code);
                    printf("--------------------------------------------------------------------------------\n");
                }
                else
                {
                    printf("Not enough stock! Availability: %d\n",Quantity[i]);
                    printf("--------------------------------------------------------------------------------\n");
                }
                break;                  // stop searching inventory once found
            }
        }
        if (!product)
        {
            printf("Product code not found!\n");
            printf("--------------------------------------------------------------------------------\n");
        }       
    }

    printf("\n\n--------------------------------------------------------------------------------\n");
    printf("Product code\t|\tQuantity in stock\t|\t\tPrice\t\t|\n");
    printf("--------------------------------------------------------------------------------\n");
    int i=0;
    for (i = 0; i < codelen; i++)
    {
        printf("%2d\t\t|\t\t%d\t\t|\t\t%.0f\t\t|\n",Productcode[i],Quantity[i],Price[i]);
        printf("--------------------------------------------------------------------------------\n");
    }
    return *total;
}

//function no.5
float displaybill(float Total)
{
    char promocode[7];
    float discount=Total;
    while (getchar() != '\n');
    printf("Enter promocode if available, otherwise press Enter: ");
    int i=0;
    while (i<7)
    {
        char ch=getchar();
        if(ch=='\n')
            break;
        else
        {
            promocode[i]=ch;
            i++;
        }
    }
    promocode[i]='\0';

    if (strcmp(promocode,"Eid2025")==0) 
    {
        discount*=0.75;
        printf("Promocode applied!\nTotal after discount: %.2f\n",discount);
        printf("--------------------------------------------------------------------------------\n");
    }

    else
    {
        printf("\nTotal bill: %.2f\n",Total);
        printf("--------------------------------------------------------------------------------\n");
    }    
    return discount;
}

//function no.6
void Invoice(char name[], char cnic[], float Total, float discount) 
{
    printf("\n===Invoice===\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Customer Name: %s\n",name);
    printf("Customer CNIC: %s\n",cnic);
    printf("Total before discount: %.2f\n",Total);

    if (Total!=discount)
        printf("Total after discount: %.2f\n",discount);
    else
        printf("No discount applied.\n");
    printf("--------------------------------------------------------------------------------\n");
}

int main()
{
    int choice;
    int Quantity[4]={50,10,20,8},Productcode[4]={1,2,3,4};
    float Price[4]={100,200,300,150},Total=0,discount=0;
    char cnic[13],name[30];
    printf("\n===Supermarket===\n");
    printf("==MENUE==\n");
    printf("1. Customer information\n2. Display inventory\n3. Update inventory\n4. Add item to cart\n5. Display total bill\n6. Show invoice\n7. Exit the system\n");
    printf("---------------------------------------------------------------------------------------\n");
    do
    {
        printf("\n\nInput selection: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                while(getchar() != '\n');            // clears the input buffer....inputting choice will leave '\n' in the buffer
                customerinformation(name,30,cnic,13);
                break;
            case 2:
                displayinventory(Productcode,4,Quantity,4,Price,4);
                break;
            case 3:
                updateinventory(Productcode,4,Quantity,4,Price,4);
                break;
            case 4:
                Total= additem(Productcode,4,Quantity,4,Price,4,&Total);
                discount=Total;
                break;
            case 5:
                discount= displaybill(Total);
                break;
            case 6:
                Invoice(name,cnic,Total,discount); 
                break;
            case 7:
                break;
            default:
                break;
        }
    } 
    while (choice>=1 && choice<7);
    return 0;

}
