void menu();
void resume();
void new_game();
void exit_game();
void replay();
void change_theme();


void menu()
{
    clearScreen();
    char choice;

    printf(
    "\t\t\tMENU\n\n\n"
    "\t\t1- Resume\n\n"
    "\t\t2- New Game\n\n"
    "\t\t3- Replay The Last Game"
    "\t\t4- Dark/Light Mode"
    "\t\t5- Exit"
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
    char mode;

    system("color F0");
    setTextColor(BLACK, WHITE2);
    clearScreen();

    printf("If you wish to set settings from file press '1' to skip, else press '2' to continue.\n");
    do
    {
        mode = getch();
    } while (mode != '1' && mode != '2');
    
    if (mode == '2') new_game_settings();
    else if (mode == '1')file_game_setting();

    setTextColor(BLACK, WHITE2);
    start_new_game();

    end_game();
}

