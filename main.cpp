#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "headers/welcome.h"
#include "headers/table.h"
#include "headers/ship.h"
#include "headers/global.h"

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

void new_game_settings()
{
    //ingredients:
    int x, y, sizeofship=3;
    int i;
    char form;
    char trash[40];  

    //new game settings:
    printf("Please enter size of map (4-15):\n");
    scanf("%i", &areaSize);     //1- size
    printf("Enter number of ships:\n");
    scanf("%i", &nShip);        //2- ship amounts
    p1_remainingShips = p2_remainingShips = nShip;

    //player 1:
    printf("Enter player1 name:\n");
    scanf("%c", &trash[0]);     //getting ready for next "scanf"
    for (i = 0; pName1[i-1] != '\n'; i++)   
    {
        scanf("%c", &pName1[i]);//3- player1 name
    }
    pName1[i-1] = 0;

    //put && check ship in area for player 1:
    for(int i =0;i<nShip;i++)     
    {

        printf("Enter ship position \'%i\' (%s):\n", i+1, pName1);
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);    //4- player1 ships position
        if (put_ship(x,y,form,sizeofship,player1,areaSize,i,1)==1 || put_ship(x,y,form,sizeofship,player1,areaSize,i,1)==2)  //check for error
        {
            int sw=0;
            while (sw==0)
            {
                if(put_ship(x,y,form,sizeofship,player1,areaSize,i,1)==1)
                {
                    printf("ERROR: Ship exists in this area.\nPlease enter position \'%i\' again (%s):\n", i+1, pName1);
                }
                else if(put_ship(x,y,form,sizeofship,player1,areaSize,i,1)==2)
                {
                    printf("ERROR: The ship is out of the range.\nPlease enter position \'%i\' again (%s):\n", i+1, pName1);
                }
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                if (put_ship(x,y,form,sizeofship,player1,areaSize,i,1)==0) sw=1;
            }
        }
    }
    
    printf("Type something then press \'enter\' to continue:\n");
    scanf("%s",&trash);         //5- next player
    
    //player 2:
    printf("Enter player2 name:\n");
    scanf("%c", &trash[0]);     //getting ready for next "scanf"
    for (i = 0; pName2[i-1] != '\n'; i++)
    {
        scanf("%c", &pName2[i]);    //6- player2 name
    }
    pName2[i-1] = 0;
 
    //put && check ship in area for player 2:
    for(int i =0;i<nShip;i++)       
    {
        printf("Enter ship position \'%i\' (%s):\n", i+1, pName2);
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);        //7- player2 ships position
        if (put_ship(x,y,form,sizeofship,player2,areaSize,i,2)==1 || put_ship(x,y,form,sizeofship,player2,areaSize,i,2)==2)  //check for error
        {
            int sw=0;
            while (sw==0)
            {
                if(put_ship(x,y,form,sizeofship,player2,areaSize,i,2)==1)
                {
                    printf("ERROR: Ship exists in this area.\nPlease enter position \'%i\' again (%s):\n", i+1, pName2);
                }
                else if(put_ship(x,y,form,sizeofship,player2,areaSize,i,2)==2)
                {
                    printf("ERROR: The ship is out of the range.\nPlease enter position \'%i\' again (%s):\n", i+1, pName2);
                }
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                if (put_ship(x,y,form,sizeofship,player2,areaSize,i,2)==0) sw=1;
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
            while (result < 0)   //scan AGAIN
            {
                if (result < -1)
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

            if (result == 0 || result == 1)     //it's OK
            {
                clearScreen();
                printTable(pName1, pName2, player1, player2, areaSize, nRound, p1_remainingShips, p2_remainingShips);     //4- show AFTER-attack table status
                if (result==0)
                {
                    player2[x-1][y-1] = 0;          //5- don't show it in next rounds
                }      
            }
            break;

        //attacker player 2:
        case 0:
            result = fire(x, y, areaSize, player1, 2, p1_remainingShips, p2_remainingShips);
            while (result < 0)   //scan AGAIN
            {
                if (result < -1)
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

            if (result ==0 || result == 1)     //it's OK
            {
                clearScreen();
                printTable(pName1, pName2, player1, player2, areaSize, nRound, p1_remainingShips, p2_remainingShips);     //4- show AFTER-attack table status
                if (result==0)
                {
                    player1[x-1][y-1] = 0;          //5- don't show it in next rounds
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
    if (p1_remainingShips) printf("p1 wonnnnnnnnnnn"); /*player1 wins*/
    else if (p2_remainingShips) printf("p2 wonnnnnnnnnnn"); /*player2 wins*/
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
