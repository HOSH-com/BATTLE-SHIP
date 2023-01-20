/*
کتابخانۀ مورد استفاده جهت انجام محاسبات مربوط به کشتی‌ها
شامل:...
- بررسی غرق شدن کشتی‌ها
- تحلیل مختصات شلیک بازیکن
- تحلیل مختصات کشتی بازیکن
- جایگذاری کشتی بازیکن در نقشه

*/
#define BLACK 0
#define GREY 8
#define WHITE1 7
#define WHITE2 15
#define BLUE 3
#define RED 4
//main functions:
int remainingShips(int x, int y);
int fire(int &xxx, int &yyy);
int check_ship(int x,int y,char form,int sizeofship);
int put_ship(int i);

int repair_ship()
{

    while(1)
    {
        printf("\nEnter coordinates to repair your ship ('row num' [SPACE] 'column num'):");
        int x,y;
        scanf("%d %d",&x,&y);
        if (setting.nRound%2==1)
        {
            if (player1.battlefield[x-1][y-1]<0)
            {
                setting.nRound++;
                if (remainingShips(x,y)<0)
                {
                    player1.remaining_ship++;
                }
                setting.nRound--;
                player1.battlefield[x-1][y-1]*=-1;
                return 0;
            }
            else if (player1.battlefield[x-1][y-1]==0)
            {
                printf("\nTHERE ISNT ANY SHIP HERE");
            }
            else if (player1.battlefield[x-1][y-1]>0)
            {
                printf("\nTHIS SHIP DIDNT GET ANY DAMAGE TO REPAIR");
            }
            
        }
        else
        {
            if (player2.battlefield[x-1][y-1]<0)
            {
                setting.nRound++;
                if (remainingShips(x,y)<0)
                {
                    player2.remaining_ship++;
                }
                setting.nRound--;
                player2.battlefield[x-1][y-1]*=-1;
                return 0;
            }
            else if (player2.battlefield[x-1][y-1]==0)
            {
                printf("\nTHERE ISNT ANY SHIP HERE");
            }
            else if (player2.battlefield[x-1][y-1]>0)
            {
                printf("\nTHIS SHIP DIDNT GET ANY DAMAGE TO REPAIR");
            }
        }
    }
}
int remainingShips(int x, int y)
{
    //attacker player1:
    if  (setting.nRound%2==1)
    {
        int shipName = player2.battlefield[x-1][y-1]%100;
        int X = player2.ship_coordinates[shipName][0]; 
        int Y = player2.ship_coordinates[shipName][1];
        int tool = player2.ship_coordinates[shipName][2];
        int arze = player2.ship_coordinates[shipName][3];
        int form = player2.ship_coordinates[shipName][4];

            int count=0;
            for (int j = 0; j < arze; j++)
            {
                for (int i = 0; i < tool ; i++)
                {
                    if(player2.battlefield[X+j][Y+i] < -99) count++;
                }
                if (count+1==tool*arze) return -2;       //player2 ship sank (-2)    
            }
    }

    //attacker player2:
    else if (setting.nRound%2==0)
    {
        int shipName = player1.battlefield[x-1][y-1]%100;
        int X = player1.ship_coordinates[shipName][0];
        int Y = player1.ship_coordinates[shipName][1];
        int tool = player1.ship_coordinates[shipName][2];
        int arze = player1.ship_coordinates[shipName][3];
        int form = player1.ship_coordinates[shipName][4];
        
       int count=0;
            for (int j = 0; j < arze; j++)
            {
                for (int i = 0; i < tool ; i++)
                {
                    if(player1.battlefield[X+j][Y+i] < -99) count++;
                }
                if (count+1==tool*arze) return -1;       //player2 ship sank (-2)    
            }
    }
    return 0;       //DIDN'T sank (0)
}

int fire(int &xxx,int &yyy)
{       
    int result;
    int x,y;
    int command;

    printf("Enter coordinates to shot ('row num' [SPACE] 'column num'):"); //2- get the shot coord.

    if (setting.theme == 0)
    {
        setTextColor(GREY, WHITE2);
        printf("\n<IF YOU WANT TO EXIT, ENTER 0 0>");
        if (setting.nRound!=1)
        printf("\n<IF YOU WANT TO REPAIR YOUR SHIP, ENTER -1 -1>\n");
        setTextColor(BLACK, WHITE2);
    }
    else if (setting.theme == 1)
    {
        setTextColor(GREY, BLACK);
        printf("\n<IF YOU WANT TO EXIT, ENTER 0 0>");
        if (setting.nRound!=1)
        printf("\n<IF YOU WANT TO REPAIR YOUR SHIP, ENTER -1 -1>\n");
        setTextColor(WHITE2, BLACK);
    }
    
    scanf("%i %i", &x, &y);
    int X = x-1;
    int Y = y-1;
    
    while (x==0 && y==0)    //especial code to pause the game(0,0)
    {
        printf("ARE YOU SURE TO BACK TO MENU?\n"
               "     1-YES      2-NO\n");
        do
        {
            command = getch();
        } while (command!='1' && command!='2');
        
        if (command=='1') //save and exit the game
        {
            save_last_movement_or_last_round();
            return -3;      //back to MENU (-3)
        }
        else if(command=='2') //continue the game 
        {
            printf("Enter coordinates to shot ('row num' [SPACE] 'column num'):"); 
            if (setting.theme == 0)
            {
                setTextColor(GREY, WHITE2);
                printf("\n<IF YOU WANT TO EXIT, ENTER 0 0>");
                if (setting.nRound!=1)
                printf("\n<IF YOU WANT TO REPAIR YOUR SHIP, ENTER -1 -1>\n");
                setTextColor(BLACK, WHITE2);
            }
            else if (setting.theme == 1)
            {
                setTextColor(GREY, BLACK);
                printf("\n<IF YOU WANT TO EXIT, ENTER 0 0>");
                if (setting.nRound!=1)
                printf("\n<IF YOU WANT TO REPAIR YOUR SHIP, ENTER -1 -1>\n");
                setTextColor(WHITE2, BLACK);
            }
            scanf("%i %i", &x, &y);
            X = x-1;
            Y = y-1;
        }
    }

    if (x==-1 && y==-1 && setting.nRound!=1)
    {
        if (setting.nRound%2==1 && player1.repair!=0)
        {
            repair_ship();
            player1.repair--;
        }
        else if (setting.nRound%2==0 && player2.repair!=0)
        {
            repair_ship();
            player2.repair--;
        }
        else
        printf("YOU DONT HAVE ANY REPAIR ITEM");
        return 3;
    }

    if (x>setting.size_of_area || x<1 || y>setting.size_of_area || y<1 )
    {
       return -1;   //shot out of range ERROR (-1)
    }

    //attacker player1:
    if(setting.nRound%2==1)
    {
        if (player2.battlefield[X][Y] > 99)
        {
            result = remainingShips(x,y);
            if (result<0) 
            {
                player2.remaining_ship --;
                player2.battlefield[X][Y]=player2.battlefield[X][Y]*(-1);
                return 2;   //ship SANK (2)
            }
            player2.battlefield[X][Y]=player2.battlefield[X][Y]*(-1);
            return 1;        //got shot (1)
        }
        
        else if (player2.battlefield[X][Y]==0)
        {
            player2.battlefield[X][Y]=-1;
            xxx=x;
            yyy=y;
            return 0;       //MISSED shot (0)
        }

        else if (player2.battlefield[X][Y] < 0)
        {
            return -2;     //already damaged ERROR (-2)
        }
    }
    //attacker player2:
    else if(setting.nRound%2==0)
    {
        if (player1.battlefield[X][Y] > 99)
        {
            result = remainingShips(x,y);
            if (result<0) 
            {
                player1.remaining_ship --;
                player1.battlefield[X][Y]=player1.battlefield[X][Y]*(-1);
                return 2;   //ship SANK (2)
            }
            player1.battlefield[X][Y]=player1.battlefield[X][Y]*(-1);
            return 1;        //got shot (1)
        }
        
        else if (player1.battlefield[X][Y]==0)
        {
            player1.battlefield[X][Y]=-1;
            xxx=x;
            yyy=y;
            return 0;       //MISSED shot (0)
        }

        else if (player1.battlefield[X][Y] < 0)
        {
            return -2;     //already damaged ERROR (-2)
        }
    }
    return 3;           //EXTRA (3)
}

int check_ship(int x,int y,char form,int sizeofship)
{    
    if (setting.nRound%2==1)
    {
        if (x+1>setting.size_of_area || y+1>setting.size_of_area) return 2;//ship out of range ERROR (2)

        //check existence for Horizental ship in map:
        if (form =='H' || form=='h')
        {   
            if(y+sizeofship-1>setting.size_of_area-1) return 2;//ship out of range ERROR (2)
            for (int i = 0; i < sizeofship; i++)
            {
                if (player1.battlefield[x][y+i]!=0)
                {
                    return 1;       //ship existence ERROR (1)
                }            
            }
        }

        //check existence for Vertical ship in map:
        if (form=='v' || form=='V')
        { 
            if(x+sizeofship-1>setting.size_of_area-1) return 2;//ship out of range ERROR (2)
            for (int i = 0; i < sizeofship; i++)
            {
                if (player1.battlefield[x+i][y]!=0)
                {
                    return 1;       //ship existence ERROR (1)
                }            
            }
        }
    }
    else if (setting.nRound%2==0)
    {

    if (x+1>setting.size_of_area || y+1>setting.size_of_area) return 2;//ship out of range ERROR (2)

    //check existence for Horizental ship in map:
    if (form =='H' || form=='h')
    {   
        if(y+sizeofship-1>setting.size_of_area-1) return 2;//ship out of range ERROR (2)
        for (int i = 0; i < sizeofship; i++)
        {
            if (player2.battlefield[x][y+i]!=0)
            {
                return 1;       //ship existence ERROR (1)
            }            
        }
    }

    //check existence for Vertical ship in map:
    if (form=='v' || form=='V')
    { 
        if(x+sizeofship-1>setting.size_of_area-1) return 2;//ship out of range ERROR (2)
        for (int i = 0; i < sizeofship; i++)
        {
            if (player2.battlefield[x+i][y]!=0)
            {
                return 1;       //ship existence ERROR (1)
            }            
        }
    }
    }
    
    return 0;       //EXTRA (3)
}//?done

int put_ship(int shipname)//*shipname is the name of the ship like ship1 or ship2
{
    char trash[40];
    char form;
    int x,y;
    int result;
    do
    {
    scanf("%d%d%c%c",&x,&y,&trash[0],&form);
    x = x-1;
    y = y-1;
    //check for errors:
    result = check_ship(x,y,form,sizeofship);
    if (result==1 || result==2)  //check for error
        {
                if(result == 1)
                {
                    if (setting.theme==0)
                    {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    }
                    else
                    {
                    setTextColor(RED, BLACK);
                    printf("ERROR: ");
                    setTextColor(WHITE2,BLACK);
                    }
                    printf("Ship exists in this area.\nPlease enter position \"%i\" again ('row' [SPACE] 'column' [SPACE] 'h/v'):\n", shipname+1);
                }
                else if(result == 2)
                {
                    if (setting.theme==0)
                    {
                    setTextColor(RED, WHITE2);
                    printf("ERROR: ");
                    setTextColor(BLACK, WHITE2);
                    }
                    else
                    {
                    setTextColor(RED, BLACK);
                    printf("ERROR: ");
                    setTextColor(WHITE2,BLACK);
                    }
                    printf("The ship is out of the range (the area is %ix%i)."
                    "\nPlease enter position \"%i\" again ('row' [SPACE] 'column' [SPACE] 'h/v'):\n",setting.size_of_area,setting.size_of_area,shipname+1);
                }
                
        }
    } while (result==2 || result==1);
    //putting ships:
    if (form=='H' || form=='h')     //Horizental
    {
        for (int i = 0; i < sizeofship; i++)
        {
            if (setting.nRound%2==1)
            {
                player1.battlefield[x][y+i]=100+shipname;
            }
            else if (setting.nRound%2==0)
            {
                player2.battlefield[x][y+i]=100+shipname;
            }
        }
        if (setting.nRound%2==1)
        {
            player1.ship_coordinates[shipname][0]=x;
            player1.ship_coordinates[shipname][1]=y;
            player1.ship_coordinates[shipname][2]=sizeofship;
            player1.ship_coordinates[shipname][3]=0;
        }
        else if (setting.nRound%2==0)
        {
            player2.ship_coordinates[shipname][0]=x;
            player2.ship_coordinates[shipname][1]=y;
            player2.ship_coordinates[shipname][2]=sizeofship;
            player2.ship_coordinates[shipname][3]=0;
        }
    }

    else if (form=='v' || form=='V')    //Vertical
    {
        for (int i = 0; i < sizeofship; i++)
        {
            if (setting.nRound%2==1)
            {
                player1.battlefield[x+i][y]=100+shipname;
            }
            else if (setting.nRound%2==0)
            {
                player2.battlefield[x+i][y]=100+shipname;
            }
        }
        if (setting.nRound%2==1)
        {
            player1.ship_coordinates[shipname][0]=x;
            player1.ship_coordinates[shipname][1]=y;
            player1.ship_coordinates[shipname][2]=sizeofship;
            player1.ship_coordinates[shipname][3]=1;
        }
        else if (setting.nRound%2==0)
        {
            player2.ship_coordinates[shipname][0]=x;
            player2.ship_coordinates[shipname][1]=y;
            player2.ship_coordinates[shipname][2]=sizeofship;
            player2.ship_coordinates[shipname][3]=1;
        }  
    }
    return 0;       //NO problem (0)
}