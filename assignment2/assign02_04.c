#include<stdio.h>

//function no. 1
void push(int *stack, int stacksize, int *top)
{
    if(*top==stacksize-1) 
    {
        printf("Stack Overflow!\nCannot push more elements.\n");
        printf("---------------------------------------------------------------------\n");
    }
    else
    {
        int element;
        printf("Enter an elemnet to be pushed: ");
        scanf("%d",&element);
        (*top)++; 
        stack[*top]=element; 
        printf("\n%d is now pushed into the stack.\n",element);
        printf("---------------------------------------------------------------------\n");
    }
}

//function no.2
void pop(int *stack, int *top)
{
    if(*top==-1) 
    {
        printf("Stack Underflow!\nNothing to pop.\n");
        printf("---------------------------------------------------------------------\n");
    } 
    else 
    {
        int pop=stack[*top];
        (*top)--;
        printf("\n%d popped from the stack.\n",pop);
        printf("---------------------------------------------------------------------\n");
    }
}

//function n0. 3
void peek(int *stack, int top)
{
    if(top==-1) 
    {
        printf("Stack is empty!\nNothing to view.\n");
        printf("---------------------------------------------------------------------\n");
    } 
    else 
    {
        printf("\nThe top element is: %d\n",stack[top]);
        printf("---------------------------------------------------------------------\n");
    }
}

//function no.4
void display(int *stack, int top)
{
    if(top==-1) 
    {
        printf("Stack is empty!\nNothing to display.\n");
        printf("---------------------------------------------------------------------\n");
    } 
    else 
    {
        printf("\nStack elements: ");
        for(int i=0;i<=top;i++) 
        {
            printf("%d ",stack[i]);
        }
        printf("\n---------------------------------------------------------------------\n");
    }
}

int main()
{
    int choice,stack[10],top=-1;   //-1 tells that the array is empty
    printf("\n===STACK OPERATIONS===\n");
    printf("1. PUSH\n2. POP\n3. PEEK\n4. DISPLAY\n5. EXIT\n");
    printf("---------------------------------------------------------------------\n");
    do
    {
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            push(stack,10,&top);
            break;
        case 2:
            pop(stack,&top);
            break;
        case 3:
            peek(stack,top);
            break;
        case 4:
            display(stack,top);
            break;
        case 5:
            break;
        default:
            break;
        }
    } while (choice>=1 && choice<5);
    
    return 0;
}