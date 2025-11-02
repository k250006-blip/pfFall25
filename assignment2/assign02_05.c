#include<stdio.h>
#include<string.h>

//function no. 1
void encodeMessage(char *message)
{
    //reversal step:
    int len=strlen(message);
    for (int i = 0; i < len/2; i++)
    {
        char temp=message[i];
        message[i]=message[len-i-1];
        message[len-i-1]=temp;
    }
    //toggle step:
    int i=0;
    while (message[i]!='\0')
    {
        char ch=message[i];
        ch=ch^(1<<2);
        ch=ch^(1<<5);
        message[i]=ch;
        i++;
    }
}

//function no. 2
void decodeMessage(char *message)
{
    int len=strlen(message);
    //untoggling step:
    int i=0;
    while (message[i]!='\0')
    {
        char ch=message[i];
        ch=ch^(1<<2);
        ch=ch^(1<<5);
        message[i]=ch;
        i++;
    }
    //reversal step:
    for (int i = 0; i < len/2; i++)
    {
        char temp=message[i];
        message[i]=message[len-i-1];
        message[len-i-1]=temp;
    }
}


int main()
{
    char message[100],ch;
    int choice,i=0;
    printf("\n===MENU===\n");
    printf("1. Encode Message\n2. Decode Message\n3. Exit\n");
    printf("----------------------------------------------------------------\n");
    do
    {
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            while (getchar()!='\n')   
            i=0;
            printf("\nInput Message:");
            while (i<100)
            {
                ch=getchar();
                if(ch=='\n')
                    break;
                else{
                    message[i]=ch;
                    i++;
                }
            }
            message[i]='\0';
            encodeMessage(message);
            printf("\nThe Encoded Message is: %s\n",message);
            printf("----------------------------------------------------------------\n");
            break;
        case 2:
            decodeMessage(message);
            printf("\nThe Decoded Message is: %s\n",message);
            printf("----------------------------------------------------------------\n");
            break;
        case 3:
            break;
        default:
            break;
        }
    } while (choice>=1 && choice<3);
    
    return 0;
}