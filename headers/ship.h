/*
کتابخانۀ مورد استفاده حهت انجام محاسبات مربوط به کشتی‌ها
شامل:...
- بررسی غرق شدن کشتی‌ها
- تحلیل مختصات شلیک بازیکن
- تحلیل مختصات کشتی بازیکن
- جایگذاری کشتی بازیکن در نقشه

*/

//main functions:
int remainingShips(int x, int y,int whichplayer,int A[][15]);
int fire(int x, int y ,int areaSize ,int A[][15],int whichplayer, int &p1_remainingShips, int &p2_remainingShips);
int check_ship(int x,int y,char form,int sizeofship,int A[][15],int areaSize);
int put_ship(int x,int y,char form,int sizeofship,int A[][15],int areaSize,int shipname,int player);

int remainingShips(int x, int y,int whichplayer,int A[][15])
{
    int shipName = A[x-1][y-1]%100;
    
    //attacker player1:
    if  (whichplayer==1)
    {
        int X = player2_ship_Coordinates[shipName][0]; 
        int Y = player2_ship_Coordinates[shipName][1];
        int sizeofship = player2_ship_Coordinates[shipName][2];
        int form = player2_ship_Coordinates[shipName][3];
        //Hoizental:
        if (form==0)
        {
            int count=0;
            for (int j = 0; j < sizeofship ; j++)
            {
                if(A[X][Y+j] < -999) count++;
            }
            if (count+1==sizeofship) return -2;       //player2 ship sank (-2)
        }
        //Vertical:
        else if (form==1)
        {
            int count=0;
            for (int j = 0; j <sizeofship ; j++)
            {
                if(A[X+j][Y] < -999) count++;
            }
            if (count+1==sizeofship) return -2;       //player2 ship sank (-2)
        }
    }

    //attacker player2:
    else if (whichplayer==2)
    {
        int X = player1_ship_Coordinates[shipName][0];
        int Y = player1_ship_Coordinates[shipName][1];
        int sizeofship = player1_ship_Coordinates[shipName][2];
        int form = player1_ship_Coordinates[shipName][3];
        //Horizental:
        if (form==0)
            {
                int count=0;
                for (int j = 0; j <sizeofship ; j++)
                {
                    if(A[X][Y+j] < -999) count++;
                }
                if (count+1==sizeofship) return -1;   //player1 ship sank (-1)
            }
        //Vertical:
        else if (form==1)
            {
                int count=0;
                for (int j = 0; j <sizeofship ; j++)
                {
                    if(A[X+j][Y] < -999) count++;
                }
                if (count+1==sizeofship) return -1;       //player1 ship sank (-1)
            }
    }
    return 0;       //DIDN'T sank (0)
}

int fire(int x, int y ,int areaSize ,int A[][15],int whichplayer, int &p1_remainingShips, int &p2_remainingShips)
{       
    //وای اگر خامنه ای حکم جهادم دهد
    int result;
    int X = x-1;
    int Y = y-1;
    
    if (x>areaSize || x<1 || y>areaSize || y<1 )
    {
        return -1;          //out of range ERROR (-1)
    }
    
    if (A[X][Y] > 999)
    {
        result = remainingShips(x,y,whichplayer,A);
        if (result == -1) 
        {
            p1_remainingShips --;
            A[X][Y]=A[X][Y]*(-1);
            return 2;   //ship SANK (2)
        }
        else if (result == -2) 
        {
            p2_remainingShips --;
            A[X][Y]=A[X][Y]*(-1);
            return 2;   //ship SANK (2)
        }
        A[X][Y]=A[X][Y]*(-1);
        return 1;        //got shot (1)
    }
    
    else if (A[X][Y]==0)
    {
        A[X][Y]=-1;
        return 0;       //MISSED shot (0)
    }

    else if (A[X][Y] < 0)
    {
        return -2;     //already damaged ERROR (-2)
    }

    return 3;           //EXTRA (3)
}

int check_ship(int x,int y,char form,int sizeofship,int A[][15],int areaSize)
{    
    if (x+1>areaSize || y+1>areaSize) return 2;//ship out of range ERROR (2)

    //check existence for Horizental ship in map:
    if (form =='H' || form=='h')
    {   
        if(y+sizeofship-1>areaSize-1) return 2;//ship out of range ERROR (2)
        for (int i = 0; i < sizeofship; i++)
        {
            if (A[x][y+i]!=0)
            {
                return 1;       //ship existence ERROR (1)
            }            
        }
    }

    //check existence for Vertical ship in map:
    if (form=='v' || form=='V')
    { 
        if(x+sizeofship-1>areaSize-1) return 2;//ship out of range ERROR (2)
        for (int i = 0; i < sizeofship; i++)
        {
            if (A[x+i][y]!=0)
            {
                return 1;       //ship existence ERROR (1)
            }            
        }
    }
    return 3;       //EXTRA (3)
}

int put_ship(int x,int y,char form,int sizeofship,int A[][15],int areaSize,int shipname,int player)//*shipname is the name of the ship like ship1 or ship2
{
    x = x-1;
    y = y-1;

    //check for errors:
    int result = check_ship(x,y,form,sizeofship,A,areaSize);
    if (result==1)
    {
        return 1;       //ship existence ERROR (1)
    }
    else if (result==2)
    {
        return 2;       //ship out of range ERROR (2)
    }

    //putting ships:
    if (form=='H' || form=='h')     //Horizental
    {
        for (int i = 0; i < sizeofship; i++)
        {
            A[x][y+i]=sizeofship*1000+0+shipname;
        }
        if (player==1)
        {
            player1_ship_Coordinates[shipname][0] = x;
            player1_ship_Coordinates[shipname][1] = y;
            player1_ship_Coordinates[shipname][2] = sizeofship;
            player1_ship_Coordinates[shipname][3] = 0;
        }
        else if (player==2)
        {
            player2_ship_Coordinates[shipname][0] = x;
            player2_ship_Coordinates[shipname][1] = y;
            player2_ship_Coordinates[shipname][2] = sizeofship;
            player2_ship_Coordinates[shipname][3] = 0;
        }
    }

    else if (form=='v' || form=='V')    //Vertical
    {
        for (int i = 0; i < sizeofship; i++)
        {
            A[x+i][y]=sizeofship*1000+100+shipname;
        }
        if (player==1)
        {
            player1_ship_Coordinates[shipname][0] = x;
            player1_ship_Coordinates[shipname][1] = y;
            player1_ship_Coordinates[shipname][2] = sizeofship;
            player1_ship_Coordinates[shipname][3] = 1;
        }
        else if (player==2)
        {
            player2_ship_Coordinates[shipname][0] = x;
            player2_ship_Coordinates[shipname][1] = y;
            player2_ship_Coordinates[shipname][2] = sizeofship;
            player2_ship_Coordinates[shipname][3] = 1;
        }  
    }
    return 0;       //NO problem (0)
}