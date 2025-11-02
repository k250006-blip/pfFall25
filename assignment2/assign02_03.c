#include<stdio.h>

//function no. 1
void update(int grid[][100],int row, int col, int flag, int op)
{
    if(op)
    {
        grid[row][col]|=(1<<flag);
    }
        
    else
    {
        grid[row][col]&=~(1<<flag); 
    }
}


//function no. 2
void query(int grid[][100], int row, int col)
{
    char *power=(grid[row][col]>>0)&1?"ON":"OFF";
    char *overload=(grid[row][col]>>1)&1?"YES":"NO";
    char *maintain=(grid[row][col]>>2)&1?"YES":"NO";
    printf("\nSector (%d,%d): \nPower %s\nOverload %s\nMaintenance %s\n",row,col,power,overload,maintain);
    printf("-----------------------------------------------------------------------------------------\n"); 
} 


//function no. 3
void diagnose(int grid[][100], int row, int col)
{
    int overload=0,maintain=0;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if((grid[i][j]>>1)&1)overload++;
            if((grid[i][j]>>2)&1)maintain++;
        }
    }
    printf("\nOverloaded: %d\nMaintenance Required: %d\n", overload,maintain);
    printf("-----------------------------------------------------------------------------------------\n"); 
}

int main()
{
    int grid[100][100]={0},choice,row,col,flag,operation;
    printf("\n===Power Grid Monitoring===\n");
    printf("1. Update Sector Status\n2. Query Sector Status\n3. Run System Diagnostic\n4. Exit System\n");
    printf("-----------------------------------------------------------------------------------------\n");
    do
    {
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("Enter row of sector: ");
            scanf("%d",&row);
            printf("Enter column of sector:  ");
            scanf("%d",&col);
            printf("\n0 -> Power\n1 -> Overload\n2 -> Maintenance\n");
            printf("Enter flag: ");
            scanf("%d",&flag);
            printf("\n1 -> Set\n0 -> Clear\n");
            printf("Enter Action to be performed: ");
            scanf("%d",&operation);
            update(grid,row,col,flag,operation);
            printf("Sector updated successfully!\n");
            printf("-----------------------------------------------------------------------------------------\n");
            break;
        case 2:
            printf("Enter row of sector: ");
            scanf("%d",&row);
            printf("Enter column of sector:  ");
            scanf("%d",&col);
            query(grid,row,col);
            break;
        case 3:
            diagnose(grid,100,100);
            break;
        case 4:
            break;
        default:
            break;
        }
    } while (choice>=1 && choice<4);
    
    return 0;
}