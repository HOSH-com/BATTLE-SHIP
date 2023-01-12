void menu();
void resume();
void new_game();
void exit_game();
void replay();
void change_theme();

#define ESC 27


void menu()
{
    clearScreen();
    char choice;
    if (setting.theme==0) system("color F0"); //apply the default theme
    else system("color 0F");
    if (setting.theme==0)
        {
            setTextColor(BLACK,WHITE2);
            printf(
        "\n\n\n"
        "           MENU:\n\n"
        "                1- Resume\n\n"
        "                2- New Game\n\n"
        "                3- Replay The Last Match\n\n"
        "                4- Dark/Light Mode\n\n"
        "                5- Exit"
        );

        }
        else if(setting.theme==1)
        {
            setTextColor(WHITE2,BLACK);
            printf(
        "\n\n\n"
        "           MENU:\n\n"
        "                1- Resume\n\n"
        "                2- New Game\n\n"
        "                3- Replay The Last Match\n\n"
        "                4- Dark/Light Mode\n\n"
        "                5- Exit"
        );
        }
    do
    {
        choice = getch();
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5');

    switch (choice)
    {
    case '1':
        resume();
        break;
    
    case '2':
        new_game();
        break;
    
    case '3':
        replay();
        break;
    
    case '4':
        change_theme();
        break;

    case '5':
        exit_game();
        break;
    
    default:
        break;
    }

}

void resume()
{
    read_last_movement_or_last_round();

    int x, y, result;

    clearScreen();
    //start the new game:
    for (; player1.remaining_ship && player2.remaining_ship; setting.nRound++)
    {
        file_save_round();
        printTable(); //1- show PRE-attack table status
        printf("Enter coordinates to shot ('row number' space 'column')\n<IF YOU WANT TO ESC PRESS 0 0>:\n"); //2- get the shot coord.
        if (setting.theme==0)
        {
            setTextColor(BLACK,WHITE2);
        }
        else if(setting.theme==1)
        {
            setTextColor(WHITE2,BLACK);
        }

        result = fire(x,y);

        while (result < 0)   //check for ERRORS
        {
            if (result == -2)
            {
                setTextColor(RED, 15);
                printf("ERROR: ");
                setTextColor(BLACK, 15);
                printf("The ship in this area is damaged already.\n");
            }
            else if (result == -1)
            {
                setTextColor(RED, 15);
                printf("ERROR: ");
                setTextColor(BLACK, 15);
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

void new_game()
{
    clearScreen();
    char mode;
    if (setting.theme==0)
    {
        system("color F0");
        setTextColor(BLACK, WHITE2);
        clearScreen();
    }
    else if (setting.theme==1)
    {
        system("color 0F");
        setTextColor(WHITE2, BLACK);
        clearScreen();
    }
    //printf("If you wish to set settings from file press '1' to skip, else press '2' to continue.\n");
    printf(
        "\n\n\n"
        "           NEW GAME:\n\n"
        "                    1- Start\n\n"
        "                    2- Set File Settings\n\n"
        "                    3- Back"
    );


    do
    {
        mode = getch();
    } while (mode != '1' && mode != '2' && mode != '3');
    
    switch (mode)
    {
    case '1':
        {
            FILE *ftemp = fopen("replay.dat", "wb");
            fclose(ftemp);
            new_game_settings();
            break;
        }
    case '2':
        {
            FILE *ftemp = fopen("replay.dat", "wb");
            fclose(ftemp);
            file_game_setting();
            break;
        }
    case '3':
        menu();
        break;
    }

    setTextColor(BLACK, WHITE2);
    start_new_game();

    end_game();
}

void replay()
{
    file_replay();
    menu();
}

void change_theme()     /*کد تغییر زمینه */
{
    clearScreen();
    printf("Which theme do you prefer?\nWHITE<0> or DARK<1>\nENTER THE CODE\n");
    int command;
    scanf("%d",&command);
    if(command==0)
    {
        setting.theme=0;
    }
    else if (command==1)
    {
        setting.theme=1;
    }
    menu();
}
void exit_game()
{
    /*کد خروج از بازی*/
    exit(1);
}

