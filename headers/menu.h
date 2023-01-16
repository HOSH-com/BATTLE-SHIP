void menu();
void resume();
void new_game();
void exit_game();
void replay();
void change_theme();




void menu()
{
    while (TRUE)
    {
        clearScreen();
        char choice;
        if (setting.theme==0) system("color F0"); //apply the default theme
        else system("color 0F");

        printf(
            "\n\n\n"
            "           MENU:\n\n"
            "                1- Resume\n\n"
            "                2- New Game\n\n"
            "                3- Replay The Last Match\n\n"
            "                4- Dark/Light Mode\n\n"
            "                5- Exit"
        );

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
}

void resume()
{   
    read_last_movement_or_last_round();
    if (setting.status == 1)
    {
        resume_game();
        end_game();
    }
    else        //if the last game was finished
    {
        clearScreen();
        printf("\n\n\n          NOT FOUND ANY UNFINISHED MATCH.\n          Returning to menu...\n");
        sleep(5000);
    }
}

void new_game()
{
    clearScreen();
    if (setting.theme==0) system("color F0");
    else system("color 0F");
    char mode;
    
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
            setting.status = 1;
            FILE *ftemp = fopen("replay.dat", "wb");    //remove the last game replay
            fclose(ftemp);
            ftemp = fopen("continue.dat", "wb");    //remove the last game continue
            fclose(ftemp);
            new_game_settings();
            break;
        }
    case '2':
        {
            setting.status = 1;
            FILE *ftemp = fopen("replay.dat", "wb");    //remove the last game replay
            fclose(ftemp);
            ftemp = fopen("continue.dat", "wb");    //remove the last game continue
            fclose(ftemp);
            file_game_setting();
            break;
        }
    case '3':
        return;
        break;
    }

    start_game();
    end_game();
}

void replay()
{
    file_replay();
}

void change_theme()     /*کد تغییر زمینه */
{
    if (setting.theme==0)       //if white, change it to black
    {
        setting.theme = 1;
        system("color 0F");
    }
    else                        //if black, change it to white
    {
        setting.theme = 0;
        system("color F0");
    }
}

void exit_game()
{
    clearScreen();
    int command;

    printf(
        "\n\n\n"
        "           EXIT:\n\n"
        "                ARE YOU SURE TO EXIT THE GAME?\n\n"
        "                       1-YES      2-NO\n"
    );
    
    do
    {
        command = getch();
    } while (command!='1' && command!='2');
        
    if (command == '1') 
    {
        clearScreen();
        system("color 07");
        exit (1);
    }
    //else return;
}

