void fire(int x,int y,int A[][15])
{
    A[x-1][y-1]=-1;
}
int check_ship(int x,int y,char form,int sizeofship,int A[][15],int areaSize)
{    
    if (form =='H' || form=='h')//check existence for horizontal ship in map1
    { 
        if(x+sizeofship>areaSize-1) return 1;
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
        if(y+sizeofship>areaSize-1) return 1;
        for (int i = 0; i < sizeofship; i++)
        {
            if (A[x+i][y]!=0)
            {
                return 1;
            }            
        }
    }
    
}
int put_ship(int x,int y,char form,int sizeofship,int A[][15],int areaSize)
{
    x = x-1;
    y = y-1;
    if (check_ship(x,y,form,sizeofship,A,areaSize)==1)
    {
        return 1;  
    }
    if (form=='H' || form=='h')
    {
        for (int i = 0; i < sizeofship; i++)
        {
            A[x][y+i]=sizeofship*10;
        }
    }
    else if (form=='v' || form=='V')
    {
        for (int i = 0; i < sizeofship; i++)
        {
            A[x+i][y]=sizeofship*10+1;
        }
    }
    return 0;
}