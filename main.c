#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
typedef enum BOOL { false, true } Boolean;
#define SIZE 9
int board[SIZE][SIZE];
int cell[2];
void printBoard();
void loadBoard();
Boolean valid(int num,int arr[]);
int* empty();
Boolean solve();
int main(int argc, char *argv[])
{
    loadBoard();
    Boolean c=solve();

    printf("---------------------------------\n");
    printBoard();

}
void loadBoard()
{
    char input[100];
    FILE *file;
    file=fopen("sudoku.txt","r");
    int a=0,b=0;
    while(fgets(input,100,file)!=NULL)
    {
        for(int j=0; j<strlen(input); j++)
        {
            if(!isspace(input[j]))
            {
                board[a][b]=atoi(&input[j]);
                b++;
            }
        }
        a++;
        b=0;
    }

}
void printBoard()
{
    for(int i=0; i<SIZE; i++)
    {
        if(i%3==0&&i!=0)
            printf("- - - - - - - - - - - - \n");
        for(int j=0; j<SIZE; j++)
        {
            if(j%3==0&&j!=0)
                printf(" | ");

            printf("%d ",board[i][j]);
        }
        printf("\n");
    }
}
int* empty()
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            if(board[i][j]==0)
            {
                cell[0]=i;
                cell[1]=j;
                printf("%d %d\n",cell[0],cell[1]);
                return cell;
            }

        }
    }
    cell[0]=10;
    cell[1]=10;

    return cell;
}
Boolean valid(int num,int pos[])
{
    //check row
    for(int i=0; i<SIZE; i++)
    {
        if(board[pos[0]][i]==num&&pos[1]!=i)
            return false;
    }
    printf("row Checked\n");
    //check column
    for(int i=0; i<SIZE; i++)
    {  printf("%d",i);
        if(board[i][pos[1]]==num&&pos[0]!=i)
            return false;
    }
    printf("\ncol Checked\n");
    //check in the box
    int boxX=(int)pos[1]/3;
    int boxY=(int)pos[0]/3;

    for(int i=boxY*3; i<=boxY*3+3; i++)
    {
        for(int j=boxX*3; j<=boxX*3+3; j++)
        {
            if(board[i][j]==num&&(i!=pos[0]&&j!=pos[1]))
                return false;

        }

    }
 printf("box Checked\n");
    return true;
}
Boolean solve()
{

    int* ptr=empty();
    int row,col,arr[2];
    if(ptr[0]==10&&ptr[1]==10)
        return true;
    else{
        row=ptr[0];
        col=ptr[1];
        arr={row,col};

    }
    for(int i=1; i<=SIZE; i++)
    {
        printf("i:%d \n",i);

        if(valid(i,arr)){
         printf("ptr: %d %d\n",ptr[0],ptr[1]);
            board[row][col]=i;
            printBoard();
    printf("------------------------------------\n");
            if(solve())
                return true;
            board[row][col]=0;
        }
    }

    return false;
}

