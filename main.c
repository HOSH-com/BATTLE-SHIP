#include <stdio.h>
#include <string.h>
#include "headers/welcome.h"
#include "headers/table.h"
#include "headers/ship.h"

int player1[15][15] = {0};   //maximum battle area table is 15*15
int player2[15][15] = {0};   

int main()
{
    int areaSize, x, y, nShip,sizeofship=3;
    char form;
    char trash[10];
    char pName1[21] = {};
    char pName2[21] = {};  

    printf("Please enter size of map:\n");
    scanf("%i", &areaSize);     //1- size
    printf("Enter Number of ships:\n");
    scanf("%i", &nShip);        //2- ship amounts
    printf("Enter Player1 name:\n");
    scanf("%s", pName1);        //3- player1 name

    //put && check ship in area for player 1:
    for(int i =0;i<nShip;i++)     
    {
        printf("Enter ship position %i", i+1);
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);    //4- player1 ships position
        if (put_ship(x,y,form,sizeofship,player1)==1)   //check for error
        {
            int sw=0;
            while (sw==0)
            {
                printf("ship is exist in that area plz enter Coordinate %i again\n", i+1);
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                if (put_ship(x,y,form,sizeofship,player1)==0) sw=1;
            }
        }
    }

    printf("Press \'enter\' to continue");
    scanf("%s",&trash);         //5- next player
    
    printf("Enter player2 name:\n");
    scanf("%s", pName2);        //6- player2 name

    //put && check ship in area for player 2:
    for(int i =0;i<nShip;i++)       
    {
        printf("Enter ship position %i", i+1);
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);        //7- player2 ships position
        if (put_ship(x,y,form,sizeofship,player2)==1)   //check for error
        {
            int sw=0;
            while (sw==0)
            {
                printf("ship is exist in that area plz enter Coordinate %i again\n", i+1);
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                if (put_ship(x,y,form,sizeofship,player2)==0) sw=1;
            }
        }
    }
    printTable(pName1 , pName2, player1, player2, areaSize);
    return 0;
}
