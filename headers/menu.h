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

    printf(
        "\n\n\n"
        "           MENU:\n\n"
        "                1- Resume\n\n"
        "                2- New Game\n\n"
        "                3- Replay The Last Game\n\n"
        "                4- Dark/Light Mode\n\n"
        "                5- Exit"
    );

    do
    {
        choice = getch();
    } while (choice != '1' && choice != '2' && choice != '3');

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
    /*کد از سر گیری بازی قبلی */
}

void new_game()
{
    clearScreen();
    char mode;

    system("color F0");
    setTextColor(BLACK, WHITE2);
    clearScreen();

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
    int sw = 1;
    char choice;
    FILE* freplay = fopen("replay.dat", "r");
    if (!freplay)
    {
        printf("ERROR: can't open replay.dat\n");
        exit (-1);
    }

    clearScreen();
    fread(&last_round, sizeof(LAST_ROUND), 1, freplay);
    printTable();
    printf("\n\nPrevious[P], Next[N], End[E], Back[ESCAPE]\n");
    do
    {
        do
        {
            choice = getch();
        } while (choice != 'P', choice != 'N', choice != 'E', choice != ESC);

        switch (choice)
        {
        case 'p':
        case 'P':
            clearScreen();
            fseek(freplay, -2*sizeof(LAST_ROUND), SEEK_CUR);
            fread(&last_round, sizeof(LAST_ROUND), 1, freplay);
            printTable();
            printf("\n\nPrevious[P], Next[N], End[E], Back[ESCAPE]\n");
            break;
        
        case 'n':
        case 'N':
            if (feof(freplay))
                sw = 0;
            else
            {
                clearScreen();
                fread(&last_round, sizeof(LAST_ROUND), 1, freplay);
                printTable();
                printf("\n\nPrevious[P], Next[N], End[E], Back[ESCAPE]\n");
            }
            break;
        
        case 'e':
        case 'E':
            clearScreen();
            fseek(freplay, -sizeof(LAST_ROUND), SEEK_END);
            fread(&last_round, sizeof(LAST_ROUND), 1, freplay);
            printTable();
            printf("\n\nPrevious[P], Next[N], End[E], Back[ESCAPE]\n");
            break;
        
        case ESC:
            sw = 0;
            break;
        }
        
    } while (sw = 1);
    
    menu();
}

void change_theme()
{
    /*کد تغییر زمینه */
}

void exit_game()
{
    /*کد خروج از بازی*/
}

