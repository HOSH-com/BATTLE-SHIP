#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "headers/welcome.h"
#include "headers/game.h"
#include "headers/table.h"
#include "headers/ship.h"
#include "headers/global.h"
#include "headers/attachment.h"

int main()
{   
    system("color F0");
    setTextColor(BLACK, 15);
    new_game_settings();
    setTextColor(BLACK, 15);
    start_new_game();

    end_game();

    return 0;
}
