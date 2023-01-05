#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "headers/welcome.h"
#include "headers/table.h"
#include "headers/ship.h"
#include "headers/global.h"
#include "headers/game.h"

#define BLACK 0
#define GREY 8
#define WHITE1 7
#define WHITE2 15
#define BLUE 3
#define RED 4

//global variables:
int nRound, nShip;
int p1_remainingShips;
int p2_remainingShips;
int player1[15][15] = {0}, player2[15][15] = {0};   //maximum battlefield table is 15*15  
char pName1[21], pName2[21]; 

//tools:
void clearScreen();
void sleep(unsigned int mseconds);
void setTextColor(int textColor, int backColor);

//main functions:
void new_game_settings();
void start_new_game();
void end_game();

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

void clearScreen()
{
    system("cls");
}

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

