#include <stdio.h>
int player1_ship_Coordinates[20][4];
int player2_ship_Coordinates[20][4];
int remainingShips(int x, int y,int whichplayer,int A[][15])
{
        int nship=A[x-1][y-1]%100;
    if  (whichplayer==1)
    {
        int sizeofship=player2_ship_Coordinates[nship][2];
        int form=player2_ship_Coordinates[nship][3];
        int X=player2_ship_Coordinates[nship][0];
        int Y=player2_ship_Coordinates[nship][1];
            if (form==0)
            {
                int count=0;
                for (int j = 0; j <sizeofship ; j++)
                {
                    if(A[X][Y+j]<0) count++;
                }
                if (count==sizeofship) return -1;
            }
            else if (form==1)
            {
                int count=0;
                for (int j = 0; j <sizeofship ; j++)
                {
                    if(A[X+j][Y]<0) count++;
                }
                if (count==sizeofship) return -1;
            }
    }
    else if (whichplayer==2)
    {
        int sizeofship=player1_ship_Coordinates[nship][2];
        int form=player1_ship_Coordinates[nship][3];
        int X=player1_ship_Coordinates[nship][0];
        int Y=player1_ship_Coordinates[nship][1];
        if (form==0)
            {
                int count=0;
                for (int j = 0; j <sizeofship ; j++)
                {
                    if(A[X][Y+j]<0) count++;
                }
                if (count==sizeofship) return -1;
            }
            else if (form==1)
            {
                int count=0;
                for (int j = 0; j <sizeofship ; j++)
                {
                    if(A[X+j][Y]<0) count++;
                }
                if (count==sizeofship) return -1;
            }
    }
    return 0;
}
int fire(int x, int y ,int areaSize ,int A[][15],int whichplayer)
{       
    //وای اگر خامنه ای حکم جهادم دهد
    
    int X = x-1;
    int Y = y-1;
    
    if (x>areaSize || x<1 || y>areaSize || y<1 )
    {
        return -1;
    }
    
    if (A[X][Y]>0)
    {
        A[X][Y]=A[X][Y]*-1;
       if (remainingShips(x,y,whichplayer,A)==-1) 
       {
       return 2;
       }
        return 1;
    }
    
    else if (A[X][Y]==0)
    {
        A[X][Y]=-1;
        return 0;
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
           player2_ship_Coordinates[shipname][0]=x;
           player2_ship_Coordinates[shipname][1]=y;
           player2_ship_Coordinates[shipname][2]=sizeofship;
           player2_ship_Coordinates[shipname][3]=0;

        }
        
        
    }
    else if (form=='v' || form=='V')
    {
        for (int i = 0; i < sizeofship; i++)
        {
            A[x+i][y]=sizeofship*10000+1000+shipname;
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
           player2_ship_Coordinates[shipname][0]=x;
           player2_ship_Coordinates[shipname][1]=y;
           player2_ship_Coordinates[shipname][2]=sizeofship;
           player2_ship_Coordinates[shipname][3]=1;
        }
        
    }
    return 0;
}