#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;
int mat[4][4]={{0,0,0,0},
               {0,0,0,0},
               {0,0,0,0},
               {0,0,0,0}};
int temp[4][4]={{0,0,0,0},
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}};
int score=0;
bool GameOver=false;
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
bool isGameOver()
{
    for (int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(mat[i][j]==0)
            return false;
            if(j!=3 && mat[i][j]==mat[i][j+1])
            return false;
            if(i!=3 && mat[i][j]==mat[i+1][j])
            return false;
        }
    }
    return true;
}
void addNumber()
{
    int x,y;
    do{
        x=rand()%4;
        y=rand()%4;
    }while(mat[x][y]!=0);
    if(rand()%4 < 3) mat[x][y]=2;
    else mat[x][y]=4;
}
void Draw()
{
    system("cls");
    cout<<"Score :: "<<score<<endl;
    cout<<"-------------------------\n";
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<"| ";
            if(mat[i][j]==0)
                cout<<"    ";
            else if(mat[i][j]<10)
                cout<<"   "<<mat[i][j];
            else if(mat[i][j]<100)
                cout<<"  "<<mat[i][j];
            else if(mat[i][j]<1000)
                cout<<" "<<mat[i][j];
            else if(mat[i][j]<10000)
                cout<<mat[i][j];
        }  
        cout<<"|"<<endl;
        cout<<"-------------------------\n";
    }
        
}
void slide()
{
    for(int i=0;i<4;i++)
    {
        int temp[4],index=0;
        for(int j=0;j<4;j++)
            temp[j]=0;
        for(int j=0;j<4;j++)
        {
            if(mat[i][j]!=0)
            {
                temp[index]=mat[i][j];
                index++;
            }
        }
        for(int j=0;j<4;j++)
            mat[i][j]=temp[j];
    }
}
void combine()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(mat[i][j]==mat[i][j+1])
            {
                mat[i][j]=mat[i][j]+mat[i][j+1];
                mat[i][j+1]=0;
                score=score+mat[i][j];
            }
        }
    }
}
void operate()
{
    slide();
    combine();
    slide();
}
bool compare()
{
    for (int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(temp[i][j]!=mat[i][j])
                return true;
    return false;
}
void flipGrid()
{
    for (int i=0;i<4;i++)
    {
        swap(&mat[i][0],&mat[i][3]);
        swap(&mat[i][1],&mat[i][2]);
    }
}
void rotateGrid()
{
    int copy[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    for (int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            copy[i][j]=mat[i][j];
    for (int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            mat[j][i]=copy[i][j];
}
void keyPressed()
{
    bool flipped=false,rotated=false,played=true;
    switch (getch())
    {
        case 'w':
            rotateGrid();
            rotated=true;
        break;
        case 's':
            rotateGrid();
            flipGrid();
            rotated=true;
            flipped=true;
        break;
        case 'd':
            flipGrid();
            flipped=true;
        break;
        case 'a':
        break;
        default:
            played=false;
            break;
    }
    if(played)
    {
        for (int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                temp[i][j]=mat[i][j];
        operate();
        bool changed=compare();     //compares temp and mat
        if(flipped)
            flipGrid();
        if(rotated)
        {
            rotateGrid();
            rotateGrid();
            rotateGrid();
        }
        if(changed)
            addNumber();
        if(isGameOver())
            GameOver=true;
    }
}
int main()
{
    srand(time(0));
    addNumber();
    addNumber();
    Draw();
    do{
        keyPressed();
        Draw();
    }while(!GameOver);
    if(GameOver)
    cout<<"\nGame Over\n";
    cout<<"\nPress any key to exit ";
    getch();
}