/*
کتابخانۀ مورد استفاده برای انجام بازی 
شامل:...
- new game settings
- start the new game
- resume the last unfinished game
- end of the game

*/



//main functions:
void new_game_settings();
void start_game();
void resume_game();
void end_game();

int nShip;

void new_game_settings()
{
    clean_battlefields();
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
        printf("Enter ship position \"%i\" ('row' [SPACE] 'column' [SPACE] 'h/v'):\n", i+1);
        put_ship(i);
    }
    
    printf("Type something then press [ENTER] to continue:\n");
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
        printf("Enter ship position \"%i\" ('row' [SPACE] 'column' [SPACE] 'h/v'):\n", i+1);
        put_ship(i);
    }
    printf("...");
    sleep(5000);
    setting.nRound++;
}

void start_game()
{
    int x, y, result;
    if (setting.theme==0) setTextColor(BLACK, WHITE2);
    else setTextColor(WHITE2, BLACK);
    clearScreen();
    //start the new game:
    for (setting.nRound=1; player1.remaining_ship && player2.remaining_ship; setting.nRound++)
    {
        save_last_movement_or_last_round();                     
        file_save_round();
        printTable(); //1- show PRE-attack table status
        printf("Enter coordinates to shot ('row num' [SPACE] 'column num'):"); //2- get the shot coord.
        if (setting.theme == 0)
        {
            setTextColor(GREY, WHITE2);
            printf("<IF YOU WANT TO EXIT, ENTER 0 0>\n");
            setTextColor(BLACK, WHITE2);
        }
        else if (setting.theme == 1)
        {
            setTextColor(GREY, BLACK);
            printf("<IF YOU WANT TO EXIT, ENTER 0 0>\n");
            setTextColor(WHITE2, BLACK);
        }
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
            else if (result == -3) return;      //back to MENU
            printf("Enter your shot again('row number' [SPACE] 'column'):\n");

            result = fire(x,y);
        }

        if (result == 0 || result == 1 || result==2)     //it's OK
        {
            clearScreen();
            file_save_round();
            printTable();     //3- show AFTER-attack table status
            if (result==2)
            {
                if (setting.nRound%2 == 1)
                    printf("One of %s's ships sank!\n", player2.name);    //ship SANK
                else
                    printf("One of %s's ships sank!\n", player1.name);    //ship SANK
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

void resume_game()      /*the same start_game but without nRound=1 */
{
    int x, y, result;
    if (setting.theme==0) setTextColor(BLACK, WHITE2);
    else setTextColor(WHITE2, BLACK);

    clearScreen();
    //start the new game:
    for (; player1.remaining_ship && player2.remaining_ship; setting.nRound++)
    {
        save_last_movement_or_last_round();                             
        file_save_round();
        printTable(); //1- show PRE-attack table status
        printf("Enter coordinates to shot ('row num' [SPACE] 'column num'):"); //2- get the shot coord.
        if (setting.theme == 0)
        {
            setTextColor(GREY, WHITE2);
            printf("<IF YOU WANT TO EXIT, ENTER 0 0>\n");
            setTextColor(BLACK, WHITE2);
        }
        else if (setting.theme == 1)
        {
            setTextColor(GREY, BLACK);
            printf("<IF YOU WANT TO EXIT, ENTER 0 0>\n");
            setTextColor(WHITE2, BLACK);
        }
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
            else if (result == -3) return;      //back to MENU
            printf("Enter your shot again('row number' [SPACE] 'column'):\n");

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
    //no winner:
    if (player1.remaining_ship && player2.remaining_ship)
        printf("Returning to menu...\n");
    //player1 wins:
    else if (player1.remaining_ship) 
    {
        printf("PLAYER \"%s\" WONNNNNNNNN!...\n", player1.name); 
        setting.status = 0;
        save_last_movement_or_last_round();
    }
    //player2 wins:
    else if (player2.remaining_ship) 
    {
        printf("PLAYER \"%s\" WONNNNNNNNN!...\n", player2.name);    
        setting.status = 0;
        save_last_movement_or_last_round();
    }
    
    sleep(3000);
}
