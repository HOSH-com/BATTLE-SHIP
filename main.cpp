#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "headers/welcome.h"
#include "headers/table.h"
#include "headers/ship.h"
#include "headers/global.h"

//global variables:
int nRound, nShip, areaSize;
int p1_remainingShips;
int p2_remainingShips;
int player1[15][15] = {0}, player2[15][15] = {0};   //maximum battlefield table is 15*15  
char pName1[21], pName2[21]; 

//tools:
void clearScreen();
void sleep(unsigned int mseconds);

//main functions:
void new_game_settings();
void start_new_game();
void end_game();

int main()
{
    new_game_settings();
    
    start_new_game();

    end_game();

    return 0;
}

//functions difinition:
void new_game_settings()
{
    //ingredients:
    int x, y, sizeofship=3;
    int i, result;
    char form;
    char trash[40];  

    //in common settings:
    do
    {
        printf("Please enter size of map (4-15):\n");
        scanf("%i", &areaSize);     //1- area size
        if (areaSize > 15 || areaSize < 4)  //check for ERROR
        {
            printf("ERROR: Enter size of map again (from 4 to 15):\n");
            scanf("%i", &areaSize);
        }
    } while (areaSize > 15 || areaSize < 4);
    printf("Enter number of ships:\n");
    scanf("%i", &nShip);        //2- ship amounts
    p1_remainingShips = p2_remainingShips = nShip;
    sleep(3000);
    clearScreen();

    //player 1:
    printf("PLAYER 1:\n\n"
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
        printf("Enter ship position \"%i\" ('row' space 'column'):\n", i+1);
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);    //4- player1 ships position
        result = put_ship(x,y,form,sizeofship,player1,areaSize,i,1);
        if (result==1 || result==2)  //check for error
        {
            int sw=0;
            while (sw==0)
            {
                if(result == 1)
                {
                    printf("ERROR: Ship exists in this area.\nPlease enter position \"%i\" again ('row' space 'column'):\n", i+1);
                }
                else if(result == 2)
                {
                    printf("ERROR: The ship is out of the range (the area is %ix%i)."
                    "\nPlease enter position \"%i\" again ('row' space 'column'):\n", areaSize, areaSize ,i+1);
                }
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                result = put_ship(x,y,form,sizeofship,player1,areaSize,i,2);
                if (result==0) sw=1;
            }
        }
    }
    
    printf("Type something then press \"enter\" to continue:\n");
    scanf("%s",&trash);         //5- next player
    clearScreen();

    //player 2:
    printf("PLAYER 2:\n\n"
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
        printf("Enter ship position \"%i\" ('row' space 'column'):\n", i+1);
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);        //7- player2 ships position
        result = put_ship(x,y,form,sizeofship,player2,areaSize,i,2);
        if (result == 1 || result == 2)  //check for error
        {
            int sw=0;
            while (sw==0)
            {
                if(result == 1)
                {
                    printf("ERROR: Ship exists in this area.\nPlease enter position \"%i\" again ('row' space 'column'):\n", i+1);
                }
                else if(result == 2)
                {
                    printf("ERROR: The ship is out of the range (the area is %ix%i)."
                    "\nPlease enter position \"%i\" again ('row' space 'column'):\n", areaSize, areaSize ,i+1);
                }
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                result = put_ship(x,y,form,sizeofship,player2,areaSize,i,2);
                if (result == 0) sw=1;
            }
        }
    }
}

void start_new_game()
{
    int x, y, result;

    sleep(5000);
    clearScreen();
    //start the new game:
    for (nRound = 1; p1_remainingShips && p2_remainingShips; nRound++)
    {
        /*playing codes*/
        printTable(pName1, pName2, player1, player2, areaSize, nRound, p1_remainingShips, p2_remainingShips); //1- show PRE-attack table status
        printf("Enter coordinates to shot (\"row number\" space \"column number\"):\n"); //2- get the shot coord.
        scanf("%i %i", &x, &y);      

        switch (nRound % 2)
        {
        //attacker player 1:
        case 1:
            result = fire(x, y, areaSize, player2, 1, p1_remainingShips, p2_remainingShips);
            while (result < 0)   //check for ERRORS
            {
                if (result == -2)
                {
                    printf("ERROR: The ship in this area is damaged already.\n");
                }
                else if (result == -1)
                {
                    printf("ERROR: The shot is out of the range (min=1, max=%i).\n", areaSize);
                }
                printf("Enter your shot again(\"row number\" space \"column number\"):\n");
                scanf("%i %i", &x, &y); 
                result = fire(x, y, areaSize, player2, 1, p1_remainingShips, p2_remainingShips);
            }

            if (result == 0 || result == 1 || result==2)     //it's OK
            {
                clearScreen();
                printTable(pName1, pName2, player1, player2, areaSize, nRound, p1_remainingShips, p2_remainingShips);     //4- show AFTER-attack table status
                if (result==2)
                {
                    printf("One of %s's ships sank!\n", pName2);    //ship SANK
                }
                else if (result==0)
                {
                    player2[x-1][y-1] = 0;          //DON'T show it in next rounds
                }      
            }
            break;

        //attacker player 2:
        case 0:
            result = fire(x, y, areaSize, player1, 2, p1_remainingShips, p2_remainingShips);
            while (result < 0)   //check for ERRORS
            {
                if (result == -2)
                {
                    printf("ERROR: The ship in this area is damaged already.\n");
                    
                }
                else if (result == -1)
                {
                    printf("ERROR: The shot is out of the range (min=1, max=%i).\n", areaSize);
                }
                printf("Enter your shot again(\"row number\" space \"column number\"):\n");
                scanf("%i %i", &x, &y); 
                result = fire(x, y, areaSize, player1, 2, p1_remainingShips, p2_remainingShips);
            }

            if (result ==0 || result == 1 || result == 2)     //it's OK
            {
                clearScreen();
                printTable(pName1, pName2, player1, player2, areaSize, nRound, p1_remainingShips, p2_remainingShips);     //4- show AFTER-attack table status
                if (result==2)
                {
                    printf("One of %s's ships sank!\n", pName1);    //ship SANK
                }
                else if (result==0)                {
                    player1[x-1][y-1] = 0;          //DON'T show it in next rounds
                }  
            }
            break;
        }
        
        /*delay and clearScreen after each round*/
        sleep(5000);
        clearScreen();      //6- clear screen
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
