#include <stdio.h>
int player1_ship_Coordinates[20][4];
int player2_ship_Coordinates[20][4];
int fire(int A[][15])
{       
        //وای اگر خامنه ای حکم جهادم بدهد
        int x,y;
        printf("Enter coordinates to shot:\n");
        scanf("%d%d",&x,&y);
        if (A[x][y]>0)
        {
            A[x][y]=A[x][y]*-1;
        }
        else if (A[x][y]==0)
        {
            A[x][y]=-1;
            return 0;
        }
        else if (A[x][y]<0)
        {
            printf("This area is damaged already\n");
            fire(A);
        }
        
}
int check_ship(int x,int y,char form,int sizeofship,int A[][15],int areaSize)
{    
    if (x+1>areaSize || y+1>areaSize) return 2;//ship out of range
    if (form =='H' || form=='h')//check existence for horizontal ship in map1
    {   
        if(y+sizeofship-1>areaSize-1) return 2;//ship out of range
        for (int i = 0; i < sizeofship; i++)
        {
            if (A[x][y+i]!=0)
            {
                return 1;
            }            
        }
    }

    if (form=='v' || form=='V')//check existence for vertical ship in map
    { 
        if(x+sizeofship-1>areaSize-1) return 2;//ship out of range
        for (int i = 0; i < sizeofship; i++)
        {
            if (A[x+i][y]!=0)
            {
                return 1;
            }            
        }
    }
}

int put_ship(int x,int y,char form,int sizeofship,int A[][15],int areaSize,int shipname,int player)//*shipname is the name of the ship like ship1 or ship2
{
    x = x-1;
    y = y-1;
    //check for errors:
    if (check_ship(x,y,form,sizeofship,A,areaSize)==1)
    {
        return 1;  
    }
    if (check_ship(x,y,form,sizeofship,A,areaSize)==2)
    {
        return 2;  
    }
    //putting ships:
    if (form=='H' || form=='h')
    {
        for (int i = 0; i < sizeofship; i++)
        {
            A[x][y+i]=sizeofship*10000+0+shipname;
        }
        if (player==1)
        {
           player1_ship_Coordinates[shipname][0]=x;
           player1_ship_Coordinates[shipname][1]=y;
           player1_ship_Coordinates[shipname][2]=sizeofship;
           player1_ship_Coordinates[shipname][3]=0;
        }
        else if (player==2)
        {
           player1_ship_Coordinates[shipname][0]=x;
           player1_ship_Coordinates[shipname][1]=y;
           player1_ship_Coordinates[shipname][2]=sizeofship;
           player1_ship_Coordinates[shipname][3]=0;

        }
        
        
    }
    else if (form=='v' || form=='V')
    {
        for (int i = 0; i < sizeofship; i++)
        {
            A[x+i][y]=sizeofship*10000+10000+shipname;
        }
        if (player==1)
        {
           player1_ship_Coordinates[shipname][0]=x;
           player1_ship_Coordinates[shipname][1]=y;
           player1_ship_Coordinates[shipname][2]=sizeofship;
           player1_ship_Coordinates[shipname][3]=1;
        }
        else if (player==2)
        {
           player1_ship_Coordinates[shipname][0]=x;
           player1_ship_Coordinates[shipname][1]=y;
           player1_ship_Coordinates[shipname][2]=sizeofship;
           player1_ship_Coordinates[shipname][3]=1;
        }
        
    }
    return 0;
}