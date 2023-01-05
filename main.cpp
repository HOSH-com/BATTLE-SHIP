#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "headers/welcome.h"
#include "headers/table.h"
#include "headers/ship.h"
#include "headers/global.h"

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

//functions difinition:
void new_game_settings()
{
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
        setTextColor(RED, 15);
        printf("ERROR: ");
        setTextColor(BLACK, 15);
        printf("Enter size of map again (from 3 to 15):\n");
        scanf("%i", &setting.size_of_area);
    }
    setTextColor(BLACK, 15);
    printf("Enter number of ships:\n");
    scanf("%i", &nShip);        //2- ship amounts
    player1->remaning_ship=player1->number_of_ship=player2->remaning_ship=player2->number_of_ship= nShip;
    printf("...");
    sleep(3000);
    clearScreen();

    //player 1:
    printf("<PLAYER 1>\n\n"
    "Enter player1 name:\n");
    scanf("%c", &trash[0]);     //getting ready for next "scanf"
    for (i = 0; pName1[i-1] != '\n'; i++)   
    {
        scanf("%c", &pName1[i]);//3- player1 name
    }
    pName1[i-1] = 0;

    //put && check ship in area for player 1:
    for(int i =0;i<nShip;i++)     
    {
        printf("Enter ship position \"%i\" ('row' space 'column' space 'h/v'):\n", i+1);
        put_ship(i);
    }
    
    printf("Type something then press \"enter\" to continue:\n");
    scanf("%s",&trash);         //5- next player
    clearScreen();

    //player 2:
    printf("<PLAYER 2>\n\n"
    "Enter player2 name:\n");
    scanf("%c", &trash[0]);     //getting ready for next "scanf"
    for (i = 0; pName2[i-1] != '\n'; i++)
    {
        scanf("%c", &pName2[i]);    //6- player2 name
    }
    pName2[i-1] = 0;
 
    //put && check ship in area for player 2:
    for(int i =0;i<nShip;i++)       
    {
        printf("Enter ship position \"%i\" ('row' space 'column' space 'h/v'):\n", i+1);
        put_ship(i);
    }
    printf("...");
    sleep(5000);
}

void start_new_game()
{
    int x, y, result;

    clearScreen();
    //start the new game:
    for (setting.nRound = 1; player1->remaning_ship && player2->remaning_ship; setting.nRound++)
    {
        printTable(pName1, pName2, player1, player2, setting.size_of_area, setting.nRound, player1->remaning_ship, player2->remaning_ship); //1- show PRE-attack table status
        printf("Enter coordinates to shot ('row number' space 'column'):\n"); //2- get the shot coord.
        setTextColor(BLACK,WHITE2);      
    
            result = fire();
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
                result = fire();
            }

            if (result == 0 || result == 1 || result==2)     //it's OK
            {
                clearScreen();
                printTable(pName1, pName2, player1, player2, setting.size_of_area, setting.nRound, p1_remainingShips, p2_remainingShips);     //3- show AFTER-attack table status
                if (result==2)
                {
                    printf("One of %s's ships sank!\n", pName2);    //ship SANK
                }
                else if (result==0)
                {
                    if(setting.nRound%2==1)
                    {
                    player2->battlefield[x-1][y-1] = 0;          //DON'T show it in next rounds
                    }
                    else
                    player1->battlefield[x-1][y-1] = 0;
                }      
            }
            
        }
        
        //delay and clearScreen after each round:
        printf("...");
        sleep(5000);
        clearScreen();      
    }

}

void end_game()
{
    if (p1_remainingShips) printf("PLAYER 1 WONNNNNNNNN!"); /*player1 wins*/
    else if (p2_remainingShips) printf("PLAYER 2 WONNNNNNNNN!"); /*player2 wins*/
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

