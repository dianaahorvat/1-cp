#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAX_LENGTH=200;

typedef struct
{
    char *title;
    char **name;
} movie;

char **readMovAct(int *n)
{
    FILE *f=fopen("Movies.in","r");
    char **movAct=(char**)malloc(sizeof(char*)*MAX_LENGTH);
    for(int i=0; i<MAX_LENGTH; i++)
    {
        movAct[i]=(char*)malloc(sizeof(char)*MAX_LENGTH);
    }
    int i=0;
    while(fgets(movAct[i],MAX_LENGTH,f)!=NULL)
    {
        movAct[i][strlen(movAct[i])-1]='\0';
        i++;
    }
    *n=i;
    return movAct;

}

void initializeMovie(movie **mov)
{
    for(int i=0; i<MAX_LENGTH; i++)
    {
        mov[i]->title=(char*)malloc(sizeof(char)*MAX_LENGTH);
        mov[i]->name=(char**)malloc(sizeof(char*)*MAX_LENGTH);
        for(int j=0; j<MAX_LENGTH; j++)
        {
            mov[i]->name[j]=(char*)malloc(sizeof(char)*MAX_LENGTH);
        }
    }
}

void fillMovie(char **movAct, int *n, movie **mov, int *arr)
{
    char *token=(char*)malloc(sizeof(char)*MAX_LENGTH);
    for(int i=0; i<*n; i++)
    {
        int j=0;
        token=strtok(movAct[i],",");
        mov[i]->title=token;

        while(token!=NULL)
        {
            token=strtok(NULL,",");
            mov[i]->name[j]=token;
            j++;
        }
        arr[i]=j;
    }

}

void printMovie(movie **mov, int *arr, int *n)
{
    int j;
    for(int i=0; i<*n; i++)
    {
        printf("%s - ",mov[i]->title);
        for(j=0; j<arr[i]-2; j++)
            printf("%s, ",mov[i]->name[j]);
        printf("%s",mov[i]->name[j]);
        printf("\n");
    }

}

char *readName()
{
    char *rname=(char*)malloc(sizeof(char)*MAX_LENGTH);
    printf("Requirement 2: \n Enter the name of an actor: ");
    scanf("%[^\n]s",rname);
    return rname;

}

void findFriends(movie **mov, int *n, int *arr, char *rname)
{
    int k=0;
    for(int i=0; i<*n; i++)
    {
        for(int j=0; j<arr[i]-1; j++)
        {
            if(strcmp(rname,mov[i]->name[j])==0)
            {
                if(k==0)
                    printf("%s 's friends are: ",rname);
                for(int d=0; d<arr[i]-1; d++)
                    if(strcmp(rname,mov[i]->name[d])!=0)
                    {
                        printf("%s  ",mov[i]->name[d]);
                        k=1;
                    }
            }

        }
    }
    if(k==0)
        printf("%s has no friends:(",rname);

}

void theMostFriends(movie **mov, int *n, int *arr)
{
    char *mostFriends=(char*)malloc(sizeof(char)*MAX_LENGTH);
    int c,mx=0;
    for(int i=0;i<*n;i++)
    for(int j=0;j<arr[i]-1;j++)
    {
        c=arr[i]-2;
        for(int d=0;d<*n;d++)
            for(int e=0;e<arr[d]-1;e++)
        {
            if(strcmp(mov[d]->name[e],mov[i]->name[j])==0 && d!=i && e!=j) c+=arr[d]-2;
        }
        if(c>mx) {mx=c; mostFriends=mov[i]->name[j];}
    }
    printf("\nRequirement 3:\nThe actor with the most friends is: %s",mostFriends);

}

int main()
{
    int *n=(int*)malloc(sizeof(int)*10);
    int *arr=(int*)malloc(sizeof(int)*MAX_LENGTH);
    char **movAct=readMovAct(&n);
    movie **mov=(movie**)malloc(sizeof(movie*)*MAX_LENGTH);
    for(int i=0; i<MAX_LENGTH; i++)
    {
        mov[i]=(movie*)malloc(sizeof(movie)*MAX_LENGTH);
    }
    initializeMovie(mov);
    fillMovie(movAct,&n,mov,arr);
    printf("Requirement 1:\n");
    printMovie(mov,arr,&n);
    char *rname=readName();
    findFriends(mov,&n,arr,rname);
    theMostFriends(mov,&n,arr);

    return 0;
}
