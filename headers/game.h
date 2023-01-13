/*
کتابخانۀ مورد استفاده برای انجام بازی 
شامل:...
- new game settings
- start the new game and running the rounds
- end of the game

*/



//main functions:
void new_game_settings();
void start_new_game();
void end_game();

int nShip;

void new_game_settings()
{
    clearScreen();
    //ingredients:
    int x, y, sizeofship=3;
    int i, result;
    char form;
    char trash[40];  
    
    //in common settings:
    printf("Please enter size of map (3-15):\n");
    scanf("%i", &setting.size_of_area);     //1- area size
    while (setting.size_of_area > 15 || setting.size_of_area < 3)  //check for ERROR
    {
        if (setting.theme==0)
        {
        setTextColor(RED, 15);
        printf("ERROR: ");
        setTextColor(BLACK, 15);
        printf("Enter size of map again (from 3 to 15):\n");
        scanf("%i", &setting.size_of_area);
        }
        else if (setting.theme==1)
        {
        setTextColor(RED,0);
        printf("ERROR: ");
        setTextColor(15,0);
        printf("Enter size of map again (from 3 to 15):\n");
        scanf("%i", &setting.size_of_area);
        }
        
    }
    if (setting.theme==0)
    {
        setTextColor(BLACK, 15);
    }
    else
    {
        setTextColor(15,BLACK);
    }
    printf("Enter number of ships:\n");
    scanf("%i", &nShip);        //2- ship amounts

    player1.remaining_ship=player1.number_of_ship=player2.remaining_ship=player2.number_of_ship= nShip;
    printf("...");
    sleep(3000);
    clearScreen();

    //player 1:
    printf("<PLAYER 1>\n\n"
    "Enter player1 name:\n");
    scanf("%c", &trash[0]);     //getting ready for next "scanf"
    for (i = 0; player1.name[i-1] != '\n'; i++)   
    {
        scanf("%c", &player1.name[i]);//3- player1 name
    }
    player1.name[i-1] = 0;

    setting.nRound = 1;
    //put && check ship in area for player 1:
    for(int i =0;i<nShip;i++)     
    {
        printf("Enter ship position \"%i\" ('row' space 'column' space 'h/v'):\n", i+1);
        put_ship(i);
    }
    
    printf("Type something then press \"enter\" to continue:\n");
    scanf("%s",&trash);         //5- next player
    clearScreen();

    //player 2:
    printf("<PLAYER 2>\n\n"
    "Enter player2 name:\n");
    scanf("%c", &trash[0]);     //getting ready for next "scanf"

    for (i = 0; player2.name[i-1] != '\n'; i++)
    {
        scanf("%c", &player2.name[i]);    //6- player2 name
    }
    player2.name[i-1] = 0;

    setting.nRound++;

    //put && check ship in area for player 2:
    for(int i =0;i<nShip;i++)       
    {
        printf("Enter ship position \"%i\" ('row' space 'column' space 'h/v'):\n", i+1);
        put_ship(i);
    }
    printf("...");
    sleep(5000);
    setting.nRound++;
}

void start_new_game()
{
    int x, y, result;
    if (setting.theme==0) setTextColor(BLACK, WHITE2);
    else setTextColor(WHITE2, BLACK);

    clearScreen();
    //start the new game:
    for (setting.nRound=1; player1.remaining_ship && player2.remaining_ship; setting.nRound++)
    {
        file_save_round();
        printTable(); //1- show PRE-attack table status
        printf("Enter coordinates to shot ('row number' space 'column')\n<IF YOU WANT TO ESC PRESS 0 0>:\n"); //2- get the shot coord.
        result = fire(x,y);

        while (result < 0)   //check for ERRORS
        {
            if (result == -2)
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
                printf("The ship in this area is damaged already.\n");
            }
            else if (result == -1)
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
                printf("The shot is out of the range (min=1, max=%i).\n", setting.size_of_area);
            }
            printf("Enter your shot again('row number' space 'column'):\n");

            result = fire(x,y);
        }

        if (result == 0 || result == 1 || result==2)     //it's OK
        {
            clearScreen();
            file_save_round();
            printTable();     //3- show AFTER-attack table status
            if (result==2)
            {
                printf("One of %s's ships sank!\n", player2.name);    //ship SANK
            }
            else if (result==0)
            {
                if(setting.nRound%2==1)
                {
                    player2.battlefield[x-1][y-1] = 0;          //DON'T show it in next rounds
                }
                else
                    player1.battlefield[x-1][y-1] = 0;
            }      
        }
                             
    printf("..."); //delay and clearScreen after each round:
    sleep(5000);
    clearScreen();
    }    
}


void end_game()
{
    if (setting.theme==0) setTextColor(BLACK, WHITE2);
    else setTextColor(WHITE2, BLACK);
    //player1 wins:
    if (player1.remaining_ship) 
    {
        printf("PLAYER 1 WONNNNNNNNN!"); 
        setting.nRound = -1;    //the game is finished (-1)
    }
    //player2 wins:
    else if (player2.remaining_ship) 
    {
        printf("PLAYER 2 WONNNNNNNNN!"); 
        setting.nRound = -1;    //the game is finished (-1)
    }
    //unfinished game:
    /*کد ذخیره سازی بازی */
}
