#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "headers/global.h"
#include "headers/attachment.h"
#include "headers/ship.h"
#include "headers/table.h"
#include "headers/file.h"
#include "headers/game.h"
#include "headers/welcome.h"

int main()
{   
    char mode;

    system("color F0");
    setTextColor(BLACK, 15);

    printf("If you prefer to set settings from file press '1' to skip, else press '2' to continue.\n");
    //do
    //{
        scanf("%c", &mode);
    //} while (mode != '1' || mode != '2');
    
    if (mode == '2') new_game_settings();
    else if (mode == '1')file_game_setting();

    setTextColor(BLACK, 15);
    start_new_game();

    end_game();

    return 0;
}
