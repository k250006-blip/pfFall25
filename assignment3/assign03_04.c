#include<stdio.h>
#include<string.h>
//structure no. 1
typedef struct{
    int BookID,popularityScore,recentlyAccessed;
}Books;

//increases if book added/accessed
//gloabal variable
int count=0;

//function no. 1
void Addbook(Books Shelf[], int shelfcapacity, int ID, int score)
{
    for (int i = 0; i < shelfcapacity; i++) 
    {
        if (Shelf[i].BookID==ID)    //book alr in the shelf
        {
            Shelf[i].popularityScore=score;    //book's score updated
            Shelf[i].recentlyAccessed=++count;      //we update count..now count is 1
            return;
        }
    }
    for (int i = 0; i < shelfcapacity; i++)
    {
        if (Shelf[i].BookID==-1)     //book not there in the array
        {
            //we update all the details
            Shelf[i].BookID=ID;
            Shelf[i].popularityScore=score;
            Shelf[i].recentlyAccessed=++count;    //we update count..now count is 2
            //now array has this book inside it
            return;
        }
    }
    //shelf full so removing least used bk..
    //we go to the first position of shelf
    int minimum= 0; 
    for (int i = 1; i < shelfcapacity; i++) 
    {
        //Find the book which was least recently accessed
        if (Shelf[i].recentlyAccessed<Shelf[minimum].recentlyAccessed) 
        {
            minimum=i;      //such book found
        }
    }
    //replacing that books info with the new book info that i added
    Shelf[minimum].BookID = ID;
    Shelf[minimum].popularityScore = score;
    Shelf[minimum].recentlyAccessed = ++count;
}

//function no. 2
int Accessbook(Books Shelf[], int shelfcapacity, int ID)
{
    int found=0;
    for (int i = 0; i < shelfcapacity; i++)
    {
        if (Shelf[i].BookID==ID)
        {
            found=1;
            Shelf[i].recentlyAccessed=++count;
            return Shelf[i].popularityScore;        //gives the score
        }
    }
    //book not in shelf...
    return -1;
}
int main()
{
    printf("\n---Library Shelf System--\n");
    Books Shelf[100];
    int capacity,Q;
    char command[15];
    scanf("%d %d",&capacity,&Q);
    // Initialize shelf
    for (int i = 0; i < capacity; i++) 
    {
        Shelf[i].BookID = -1;
        Shelf[i].popularityScore = 0;
        Shelf[i].recentlyAccessed = 0;
    }
    //doing the commands thing..
    for (int i = 0; i < Q; i++)
    {
        scanf("%s", command);  //no '&'..command alr address
        if (strcmp(command,"ADD")==0) 
        {
            int ID,score;
            scanf("%d %d",&ID,&score);     //input book info
            Addbook(Shelf,capacity,ID,score);
        }
        else if (strcmp(command,"ACCESS")==0) 
        {
            int ID;
            scanf("%d",&ID);  //input j. bk id
            int access=Accessbook(Shelf,capacity,ID);
            printf("%d\n",access);
        }
    }
    return 0;
}
