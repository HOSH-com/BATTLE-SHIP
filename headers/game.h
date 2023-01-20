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



void new_game_settings() // for setting new game settings manually
{
    clean_battlefields();
    clearScreen();

    //ingredients:
    int x, y, length, width, nShip;
    int i, result, sw = 1, counter;
    char form;
    char trash[40];  
    


    //1- area size:
    printf("Please enter size of map (3-15):\n");
    scanf("%i", &setting.size_of_area);    

    while (setting.size_of_area > 15 || setting.size_of_area < 3)  //check for error
    {
        printError();
        printf("Enter size of map again (from 3 to 15):\n");
        scanf("%i", &setting.size_of_area);
    }

    //2- house amounts:
    printf("Enter maximum number of houses for putting ships:\n"); 
    scanf("%i", &setting.max_element);  
    player1.remaining_element = player2.remaining_element = setting.max_element;



    printf("...");
    sleep(3000);
    clearScreen();



    //3- player1 name:
    printf("<PLAYER 1>\n\n"
    "Enter player1 name:\n");
    scanf("%c", &trash[0]);     // get ready for next "scanf"
    for (i = 0; player1.name[i-1] != '\n'; i++)   
    {
        scanf("%c", &player1.name[i]);
    }
    player1.name[i-1] = 0;

    //4- player1 ships:
    counter = 0; // for naming ships
    turn = PLAYER1;

    printf("Enter your ships 'size' (x in y) and 'number of them' in the mentioned order " // player must put ship, at least, once
    "('%i' house(s) is left):\n", player1.remaining_element);
    scanf("%i%i%i", &width, &length, &nShip);

    while (width * length * nShip > player1.remaining_element) // check for error
    {
        printError();
        printf("House limit exeeded! You have only '%i' house(s) left.\n"
        "Enter your ships 'size' (x in y) and 'number of them' again:\n", player1.remaining_element);
        scanf("%i%i%i", &width, &length, &nShip);
    }

    player1.remaining_element -= width * length * nShip; // subtract used houses from remainings

    for (int i = 0; i < nShip; ++i)
    {
        put_ship(counter, length, width);
        ++counter;
    }

    while (sw)
    {
        printf("If you are done, type '---', else type '$$$' then press [ENTER] to continue:\n");
        result = 0;

        do // make decision
        {
            scanf("%s", trash);

            if (strcmp(trash, "$$$") == 0)
                result = 1;

            else if (strcmp(trash, "---") == 0)
            {
                result = 2;
                sw = 0;
            }    

        } while (!result);

        if (result == 1) // next ship placement
        {
            printf("Enter your ships 'size' (x in y) and 'number of them' in the mentioned order "
            "('%i' house(s) is left):\n", player1.remaining_element);
            scanf("%i%i%i", &width, &length, &nShip);

            while (width * length * nShip > player1.remaining_element) // check for error
            {
                printError();
                printf("House limit exeeded! You have only '%i' house(s) left.\n"
                "Enter your ships 'size' (x in y) and 'number of them' again:\n", player1.remaining_element);
                scanf("%i%i%i", &width, &length, &nShip);
            }

            player1.remaining_element -= width * length * nShip; // subtract used houses from remainings

            for (int i = 0; i < nShip; ++i)
            {
                put_ship(counter, length, width);
                ++counter;
            }

        }
        
    }
    
    player1.remaining_ship = player1.number_of_ship;



    clearScreen();



    // 5- player2 name:
    printf("<PLAYER 2>\n\n"
    "Enter player2 name:\n");
    scanf("%c", &trash[0]);     // get ready for next "scanf"
    for (i = 0; player2.name[i-1] != '\n'; i++)   
    {
        scanf("%c", &player2.name[i]);
    }
    player2.name[i-1] = 0;

    // 6- player2 ships:
    counter = 0; // for naming ships
    turn = PLAYER2;

    printf("Enter your ships 'size' (x in y) and 'number of them' in the mentioned order " // player must put ship, at least, once
    "('%i' house(s) is left):\n", player2.remaining_element);
    scanf("%i%i%i", &width, &length, &nShip);

    while (width * length * nShip > player2.remaining_element) // check for error
    {
        printError();
        printf("House limit exeeded! You have only '%i' house(s) left.\n"
        "Enter your ships 'size' (x in y) and 'number of them' again:\n", player2.remaining_element);
        scanf("%i%i%i", &width, &length, &nShip);
    }

    player2.remaining_element -= width * length * nShip; // subtract used houses from remainings

    for (int i = 0; i < nShip; ++i)
    {
        put_ship(counter, length, width);
        ++counter;
    }

    while (sw)
    {
        printf("If you are done, type '---', else type '$$$' then press [ENTER] to continue:\n");
        result = 0;

        do // make decision
        {
            scanf("%s", trash);

            if (strcmp(trash, "$$$") == 0)
                result = 1;

            else if (strcmp(trash, "---") == 0)
            {
                result = 2;
                sw = 0;
            }    

        } while (!result);

        if (result == 1) // next ship placement
        {
            printf("Enter your ships 'size' (x in y) and 'number of them' in the mentioned order "
            "('%i' house(s) is left):\n", player2.remaining_element);
            scanf("%i%i%i", &width, &length, &nShip);

            while (width * length * nShip > player2.remaining_element) // check for error
            {
                printError();
                printf("House limit exeeded! You have only '%i' house(s) left.\n"
                "Enter your ships 'size' (x in y) and 'number of them' again:\n", player1.remaining_element);
                scanf("%i%i%i", &width, &length, &nShip);
            }

            player2.remaining_element -= width * length * nShip; // subtract used houses from remainings

            for (int i = 0; i < nShip; ++i)
            {
                put_ship(counter, length, width);
                ++counter;
            }
            
        }
        
    }

    player2.remaining_ship = player2.number_of_ship;



    clearScreen();


    
    // 7- number of repairs:
    puts("Enter number of house repairs:");
    scanf("%i", &setting.max_repair);

    while (setting.max_repair < 0) // check for error
    {
        printError();
        printf("Your input cannot be smaller than zero!\nEnter number of house repairs again:");
        scanf("%i", &setting.max_repair);
    }
    
    player1.remaining_repair = player2.remaining_repair = setting.max_repair;



    printf("...");
    sleep(5000);
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
    //start the new game:q
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
