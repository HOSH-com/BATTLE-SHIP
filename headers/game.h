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
    int x, y, length, width, nShip, nElement, elementLeft;
    int i, result, sw, counter;
    char form;
    char trash[40];  
    char str[100] , *strPtr;
    


    //1- area size:
    printf("Please enter size of map (3-15):\n");
    fgets(str, 100, stdin);
    setting.size_of_area = strtol(str, &strPtr, 0);   
    
    while (setting.size_of_area > 15 || setting.size_of_area < 3)  //check for error
    {
        printError();
        printf("Enter size of map again (from 3 to 15):\n");
        fgets(str, 100, stdin);
        setting.size_of_area = strtol(str, &strPtr, 0);
    }

    //2- house amounts:
    printf("Enter maximum number of houses for putting ships:\n"); 
    fgets(str, 100, stdin);
    setting.max_element = strtol(str, &strPtr, 0);

    while (!(setting.max_element > 0 && setting.max_element <= setting.size_of_area * setting.size_of_area / 2)) // check for error
    {
        printError();
        printf("Enter maximum number of houses again (from 1 to %i):\n", setting.size_of_area * setting.size_of_area / 2);
        fgets(str, 100, stdin);
        setting.max_element = strtol(str, &strPtr, 0);
    } 



    printf("...");
    sleep(3000);
    clearScreen();



    //3- player1 name:
    printf("<PLAYER 1>\n\n"
    "Enter player1 name:\n");
    scanf("%c", &trash[0]);     // get ready for next "scanf"

    for (i = 0; player1.name[i-1] != '\n'; i++)   
        scanf("%c", &player1.name[i]);
    
    player1.name[i-1] = 0;

    //4- player1 ships:
    counter = 0; // for naming ships
    elementLeft = setting.max_element;
    nElement = 0;
    turn = PLAYER1;

    clearScreen();
    printPreview(player1.name);
    printf("Enter your ships 'size' (x in y) and 'number of them' in the mentioned order " // player must put ship, at least, once
    "('%i' house(s) is left):\n", elementLeft);
    scanf("%i%i%i", &width, &length, &nShip);

    while (width * length * nShip > elementLeft) // check for error
    {
        printError();
        printf("House limit exeeded! You have only '%i' house(s) left.\n"
        "Enter your ships 'size' (x in y) and 'number of them' again:\n", elementLeft);
        scanf("%i%i%i", &width, &length, &nShip);
    }

    elementLeft -= width * length * nShip; // subtract used houses from remaining elements
    nElement += length * width; // add used houses to player elements

    for (int i = 0; i < nShip; ++i)
    {
        put_ship(counter, length, width);
        clearScreen();
        printPreview(player1.name);
        ++counter;
    }

    sw = 1;

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
            "('%i' house(s) is left):\n", elementLeft);
            scanf("%i%i%i", &width, &length, &nShip);

            while (width * length * nShip > elementLeft) // check for error
            {
                printError();
                printf("House limit exeeded! You have only '%i' house(s) left.\n"
                "Enter your ships 'size' (x in y) and 'number of them' again:\n", elementLeft);
                scanf("%i%i%i", &width, &length, &nShip);
            }

            elementLeft -= width * length * nShip; // subtract used houses from remainings
            nElement += length * width; // add used houses to player elements

            for (int i = 0; i < nShip; ++i)
            {
                put_ship(counter, length, width);
                clearScreen();
                printPreview(player1.name);
                ++counter;
            }

        }
        
    }
    
    player1.remaining_ship = player1.number_of_ship;
    player1.number_of_elements = player1.remaining_element = nElement;



    clearScreen();



    // 5- player2 name:
    printf("<PLAYER 2>\n\n"
    "Enter player2 name:\n");
    scanf("%c", &trash[0]);     // get ready for next "scanf"

    for (i = 0; player2.name[i-1] != '\n'; i++)   
        scanf("%c", &player2.name[i]);
    
    player2.name[i-1] = 0;

    // 6- player2 ships:
    counter = 0; // for naming ships
    elementLeft = setting.max_element;
    nElement = 0;
    turn = PLAYER2;

    clearScreen();
    printPreview(player2.name);
    printf("Enter your ships 'size' (x in y) and 'number of them' in the mentioned order " // player must put ship, at least, once
    "('%i' house(s) is left):\n", elementLeft);
    scanf("%i%i%i", &width, &length, &nShip);

    while (width * length * nShip > elementLeft) // check for error
    {
        printError();
        printf("House limit exeeded! You have only '%i' house(s) left.\n"
        "Enter your ships 'size' (x in y) and 'number of them' again:\n", elementLeft);
        scanf("%i%i%i", &width, &length, &nShip);
    }

    elementLeft -= width * length * nShip; // subtract used houses from remainings
    nElement += length * width; // add used houses to player elements

    for (int i = 0; i < nShip; ++i)
    {
        put_ship(counter, length, width);
        clearScreen();
        printPreview(player2.name);
        ++counter;
    }

    sw = 1;

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
            "('%i' house(s) is left):\n", elementLeft);
            scanf("%i%i%i", &width, &length, &nShip);

            while (width * length * nShip > elementLeft) // check for error
            {
                printError();
                printf("House limit exeeded! You have only '%i' house(s) left.\n"
                "Enter your ships 'size' (x in y) and 'number of them' again:\n", elementLeft);
                scanf("%i%i%i", &width, &length, &nShip);
            }

            elementLeft -= width * length * nShip; // subtract used houses from remainings
            nElement += length * width; // add used houses to player elements

            for (int i = 0; i < nShip; ++i)
            {
                put_ship(counter, length, width);
                clearScreen();
                printPreview(player2.name);
                ++counter;
            }
            
        }
        
    }

    player2.remaining_ship = player2.number_of_ship;
    player2.number_of_elements = player2.remaining_element = nElement;



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
    if (theme == 0) setTextColor(BLACK, WHITE2);
    else setTextColor(WHITE2, BLACK);
    clearScreen();
    
    //start the new game:
    for (setting.nRound=1; player1.remaining_ship && player2.remaining_ship; setting.nRound++)
    {
        save_last_movement_or_last_round();                     
        file_save_round();
        printTable(); //1- show PRE-attack table status
        
        printf("         <-FIRE->\n");
        result = fire(x,y);

        while (result < 0)   //check for ERRORS or exit
        {
            if (result == -2) // invalid shot
            {
                printError();
                printf("The ship in this area is damaged already.\n");
            }

            else if (result == -1) // invalid shot
            {
                printError();
                printf("The shot is out of the range (min=1, max=%i).\n", setting.size_of_area);
            }

            else if (result == -3) //back to MENU 
                return;      

            else if (result == -4) // repair item == 0
            {
                printError();
                printf("You don't have any repair item!\n");
            }
            
            else if (result == -5) // ships are intact
            {
                printError();
                printf("Your ships are not damaged yet!\n");
            }
            
            result = fire(x,y);
        }



        // fire or repair: (result == 0 || 1 || 2 || 3)
        clearScreen();
        file_save_round();
        printTable();     //3- show AFTER-attack table status

        if (result==2) // ship SANK
        {
            if (setting.nRound%2 == 1)
                printf("One of %s's ships sank!\n", player2.name);
            else
                printf("One of %s's ships sank!\n", player1.name);    
        }

        else if (result==0) // MISSED shot
        {
            if(setting.nRound%2==1)
            {
                player2.battlefield[x-1][y-1] = 0;          //DON'T show it in next rounds
            }
            else
                player1.battlefield[x-1][y-1] = 0;
        }

        else if (result==3) // ship repaired
        {
            printf("\nYour ship repaired!\n");
        }
        


        printf("..."); //delay and clearScreen after each round:
        sleep(5000);
        clearScreen();
    }    
}



void resume_game()      /*the same start_game but without nRound=1 and an exception for file_save_round*/
{
    int x, y, result, doSave = 0;
    if (theme == 0) setTextColor(BLACK, WHITE2);
    else setTextColor(WHITE2, BLACK);
    clearScreen();

    //start the new game:
    for ( ; player1.remaining_ship && player2.remaining_ship; setting.nRound++)
    {
        save_last_movement_or_last_round();                     
        if (doSave) // avoid saving no-actions round
            file_save_round();
        printTable(); //1- show PRE-attack table status
        
        printf("         <-FIRE->\n");
        result = fire(x,y);

        while (result < 0)   //check for ERRORS or exit
        {
            if (result == -2) // invalid shot
            {
                printError();
                printf("The ship in this area is damaged already.\n");
            }

            else if (result == -1) // invalid shot
            {
                printError();
                printf("The shot is out of the range (min=1, max=%i).\n", setting.size_of_area);
            }

            else if (result == -3) //back to MENU 
                return;      

            else if (result == -4) // repair item == 0
            {
                printError();
                printf("You don't have any repair item...\n");
            }
            
            else if (result == -5) // ships are intact
            {
                printError();
                printf("Your ships are not damaged yet...\n");
            }
            
            result = fire(x,y);
        }



        // fire or repair: (result == 0 || 1 || 2 || 3)
        clearScreen();
        file_save_round();
        printTable();     //3- show AFTER-attack table status

        if (result==2) // ship SANK
        {
            if (setting.nRound%2 == 1)
                printf("One of %s's ships sank!\n", player2.name);
            else
                printf("One of %s's ships sank!\n", player1.name);    
        }

        else if (result==0) // MISSED shot
        {
            if(setting.nRound%2==1)
            {
                player2.battlefield[x-1][y-1] = 0;          //DON'T show it in next rounds
            }
            else
                player1.battlefield[x-1][y-1] = 0;
        }

        else if (result==3) // ship repaired
        {
            printf("\nYour ship repaired!\n");
        }

        doSave = 1;


        printf("..."); //delay and clearScreen after each round:
        sleep(5000);
        clearScreen();
    }    
}



void end_game()
{
    if (theme == 0) setTextColor(BLACK, WHITE2);
    else setTextColor(WHITE2, BLACK);
    //no winner:
    if (player1.remaining_ship && player2.remaining_ship)
        printf("Returning to menu...\n");
    //player1 wins:
    else if (player1.remaining_ship && !player2.remaining_ship) 
    {
        printf("PLAYER \"%s\" WONNNNNNNNN!...\n", player1.name); 
        setting.status = 0;
        save_last_movement_or_last_round();
    }
    //player2 wins:
    else if (player2.remaining_ship && !player1.remaining_ship) 
    {
        printf("PLAYER \"%s\" WONNNNNNNNN!...\n", player2.name);    
        setting.status = 0;
        save_last_movement_or_last_round();
    }

    else exit (EXIT_FAILURE);
    
    sleep(3000);
}


