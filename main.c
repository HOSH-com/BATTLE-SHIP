#include <stdio.h>
#include <string.h>
#include "headers/welcome.h"
#include "headers/table.h"
#include "headers/ship.h"

int nRound;
int p1_remainingShips;
int p2_remainingShips;
int player1[15][15] = {0};   //maximum battle area table is 15*15
int player2[15][15] = {0};   

int main()
{
    //ingredients:
    int areaSize, x, y, nShip,sizeofship=3;
    int i;
    char form;
    char trash[40];
    char pName1[21] = {};
    char pName2[21] = {};  

    //new game settings:
    printf("Please enter size of map (4-15):\n");
    scanf("%i", &areaSize);     //1- size
    printf("Enter number of ships:\n");
    scanf("%i", &nShip);        //2- ship amounts

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
        if (put_ship(x,y,form,sizeofship,player1,areaSize)==1 || put_ship(x,y,form,sizeofship,player1,areaSize)==2)  //check for error
        {
            int sw=0;
            while (sw==0)
            {
                if(put_ship(x,y,form,sizeofship,player1,areaSize)==1)
                {
                    printf("ERROR: Ship exists in this area.\nPlease enter position \'%i\' again (%s):\n", i+1, pName1);
                }
                else if(put_ship(x,y,form,sizeofship,player1,areaSize)==2)
                {
                    printf("ERROR: The ship is out of the range.\nPlease enter position \'%i\' again (%s):\n", i+1, pName1);
                }
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                if (put_ship(x,y,form,sizeofship,player1,areaSize)==0) sw=1;
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
        if (put_ship(x,y,form,sizeofship,player2,areaSize)==1 || put_ship(x,y,form,sizeofship,player2,areaSize)==2)  //check for error
        {
            int sw=0;
            while (sw==0)
            {
                if(put_ship(x,y,form,sizeofship,player2,areaSize)==1)
                {
                    printf("ERROR: Ship exists in this area.\nPlease enter position \'%i\' again (%s):\n", i+1, pName2);
                }
                else if(put_ship(x,y,form,sizeofship,player2,areaSize)==2)
                {
                    printf("ERROR: The ship is out of the range.\nPlease enter position \'%i\' again (%s):\n", i+1, pName2);
                }
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                if (put_ship(x,y,form,sizeofship,player2,areaSize)==0) sw=1;
            }
        }
    }

    //start the new game:
    for (nRound = 1; p1_remainingShips || p2_remainingShips; nRound++)
    {
        
    }
    

    return 0;
}
