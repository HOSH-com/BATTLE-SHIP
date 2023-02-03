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
int check_ship(int x, int y, int length, int width);
int put_ship(int number, int length, int width);
int exit(int &x,int &y);
int repair_ship();



int repair_ship()
{
    printf("        <-REPAIR->\n");

    while(1)
    {
        int x,y;
        if (setting.nRound%2==1)
        {
            printf("Enter coordinates to repair your ship ('%i' repair items are left):\n", player1.remaining_repair);
            scanf("%d %d",&x,&y);
            if (player1.battlefield[x-1][y-1]<0)
            {
                setting.nRound++;
                if (remainingShips(x,y)<0) // if the ship was sunk
                {
                    player1.remaining_ship++;
                }
                setting.nRound--;
                player1.battlefield[x-1][y-1]*=-1;
                return 0;
            }
            else if (player1.battlefield[x-1][y-1]==0)
            {
                printError();
                printf("There is not any ship here.\n");
            }
            else if (player1.battlefield[x-1][y-1]>0)
            {
                printError();
                printf("This house is not damaged.\n");
            }
            
        }
        else
        {
            printf("Enter coordinates to repair your ship ('%i' repair items are left):\n", player2.remaining_repair);
            scanf("%d %d",&x,&y);
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
                printError();
                printf("There is not any ship here.\n");
            }
            else if (player2.battlefield[x-1][y-1]>0)
            {
                printError();
                printf("This house is not damaged.\n");
            }
        }
    }
}



int remainingShips(int x, int y)
{
    //attacker player1:
    if  (setting.nRound%2==1)
    {   
        int shipName = abs(player2.battlefield[x-1][y-1]%100);
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
            if (count==tool*arze) return -2;       //player2 ship sank (-2)    
        }
    }

    //attacker player2:
    else if (setting.nRound%2==0)
    {
        int shipName = abs(player1.battlefield[x-1][y-1]%100);
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
            if (count==tool*arze) return -1;       //player1 ship sank (-1)    
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

    if (theme == 0)
    {
        setTextColor(GREY, WHITE2);
        printf("<ENTER 0 0 TO EXIT, -1 -1 TO REPAIR YOUR SHIP>\n");
        setTextColor(BLACK, WHITE2);
    }
    else if (theme == 1)
    {
        setTextColor(GREY, BLACK);
        printf("<ENTER 0 0 TO EXIT, -1 -1 TO REPAIR YOUR SHIP>\n");
        setTextColor(WHITE2, BLACK);
    }
    
    scanf("%i %i", &x, &y);
    int X = x-1;
    int Y = y-1;
    
    if (x==0 && y==0)    //especial code to pause the game(0 0)
    {
        if(exit(x,y)==-3)
            return -3; // back to MENU (-3)
       
       X=x-1;
       Y=y-1;
    }

    if (x==-1 && y==-1 ) // especial code to repair(-1 -1)
    {
        if (setting.nRound%2==1 && player1.remaining_repair!=0)
        {
            if (player1.number_of_elements - player1.remaining_element == 0) // if all of ships were intact (-5)
                return -5;

            repair_ship();
            player1.remaining_repair--;
            ++player1.remaining_element;
            return 3; // REPAIRED (3)
        }
        else if (setting.nRound%2==0 && player2.remaining_repair!=0)
        {
            if (player2.number_of_elements - player2.remaining_element == 0) // if all of ships were intact (-5)
                return -5;

            repair_ship();
            player2.remaining_repair--;
            ++player2.remaining_element;
            return 3; // REPAIRED (3)
        }
        else
        {
            return -4; // no repair item (-4)
        }
    }

    //*fire function ->>
    
    if (x>setting.size_of_area || x<1 || y>setting.size_of_area || y<1 )
    {
       return -1;   //shot out of range ERROR (-1)
    }

    //attacker player1:
    if(setting.nRound%2==1)
    {
        if (player2.battlefield[X][Y] > 99)
        {
            --player2.remaining_element;
            player2.battlefield[X][Y]=player2.battlefield[X][Y]*(-1);
            result = remainingShips(x,y);
            if (result<0) 
            {
                player2.remaining_ship --;
                return 2;   //ship SANK (2)
            }
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
            --player1.remaining_element;
            player1.battlefield[X][Y]=player1.battlefield[X][Y]*(-1);
            result = remainingShips(x,y);
            if (result<0) 
            {
                player1.remaining_ship --;
                return 2;   //ship SANK (2)
            }
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

    return 4; // extra
}



int check_ship(int x, int y, int length, int width)
{    
    ++x;
    ++y;

    // check range limit:
    if ((y + (length - 1) > setting.size_of_area) || (x + (width - 1) > setting.size_of_area))
    {
        return -2; // ship out of range ERROR (-2)
    }

    --x;
    --y;

    // check ship existance:
    if (turn == PLAYER1)
    {
        for (int i = x; i < width + x; ++i)
            for (int j = y; j < length + y; ++j)
                if (player1.battlefield[i][j] > 99)
                {
                    return -1; // ship existance ERROR (-1)
                }
    }

    else
    {
        for (int i = x; i < width + x; ++i)
            for (int j = y; j < length + y; ++j)
                if (player2.battlefield[i][j] > 99)
                {
                    return -1; // ship existance ERROR (-1)
                }
    }
    
    return 0; // OK (0)
}



int put_ship(int shipNumber, int length, int width)//*shipname is the name of the ship like ship1 or ship2
{
    int x, y, result;
    char trash, form;



    printf("Place ship number '%i' ('row' [SPACE] 'column' [SPACE] 'h/v form'):\n", shipNumber + 1);

    do
    {
        scanf("%d%d%c%c", &x, &y, &trash, &form);

        // correct user possible misplaced input:
        if ((form == 'h' || form == 'H') && !(length >= width)) 
            intSwap(length, width);

        else if ((form == 'v' || form == 'V') && !(width >= length))
            intSwap(length, width);

        x = x-1; // decrement for initializing battlefields
        y = y-1;
        
        // check for errors:
        result = check_ship(x, y, length, width);

        if (result == -1 || result == -2)  
        {
            if (result == -1)
            {
                printError();
                printf("Ship exists in this area.\n"
                "Place ship number '%i' again ('row' [SPACE] 'column' [SPACE] 'h/v form'):\n", shipNumber + 1);
            }

            else if (result == -2)
            {
                printError();
                printf("The ship is out of the range (the area is %ix%i).\n"
                "Place ship number '%i' again ('row' [SPACE] 'column' [SPACE] 'h/v form'):\n", setting.size_of_area, setting.size_of_area, shipNumber + 1);
            }
                
        }
        
    } while (result == -1 || result == -2);
 


    // put ships in battlefield:
    if (turn == PLAYER1)
    {
        for (int i = x; i < width + x; ++i)
            for (int j = y; j < length + y; ++j)
                player1.battlefield[i][j] = 100 + shipNumber; 

        // initialize ship coor. array:
        player1.ship_coordinates[shipNumber][0] = x;
        player1.ship_coordinates[shipNumber][1] = y;
        player1.ship_coordinates[shipNumber][2] = length;
        player1.ship_coordinates[shipNumber][3] = width;
        player1.ship_coordinates[shipNumber][4] = form;

        ++player1.number_of_ship;
    }

    else if (turn == PLAYER2)
    {
        for (int i = x; i < width + x; ++i)
            for (int j = y; j < length + y; ++j)
                player2.battlefield[i][j] = 100 + shipNumber;  
                
        // initialize ship coor. array:
        player2.ship_coordinates[shipNumber][0] = x;
        player2.ship_coordinates[shipNumber][1] = y;
        player2.ship_coordinates[shipNumber][2] = length;
        player2.ship_coordinates[shipNumber][3] = width;
        player2.ship_coordinates[shipNumber][4] = form;

        ++player2.number_of_ship;
    }

    return 0;       //NO problem (0)
}



int  exit(int &x,int &y)
{
    int command;
    while (x==0 && y==0)    //especial code to pause the game(0,0)
    {
        printf(
            "         <-EXIT->\n"
            "ARE YOU SURE TO BACK TO MENU?     1-YES      2-NO\n");
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
            printf("         <-FIRE->\n");
            printf("Enter coordinates to shot ('row num' [SPACE] 'column num'):"); 
            if (theme == 0)
            {
                setTextColor(GREY, WHITE2);
                printf("<ENTER 0 0 TO EXIT, -1 -1 TO REPAIR YOUR SHIP>\n");
                setTextColor(BLACK, WHITE2);
            }
            else if (theme == 1)
            {
                setTextColor(GREY, BLACK);
                printf("<ENTER 0 0 TO EXIT, -1 -1 TO REPAIR YOUR SHIP>\n");
                setTextColor(WHITE2, BLACK);
            }
            scanf("%i %i", &x, &y);
        }
    }

    return 0; // extra
}