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
    scanf("%i", &areaSize);     //1- size
    scanf("%i", &nShip);        //2- ship amounts
    scanf("%s", pName1);        //3- player1 name
    scanf("%s", pName2);        //4- player2 name
    for(int i =0;i<nShip;i++)
    {
        scanf("%d%d",&x,&y);
        scanf("%c%c",&trash[0],&form);
    if (put_ship(x,y,form,sizeofship,player1)==1)
    {
        int sw=0;
        while (sw==0)
        {
            printf("ship is exist in that area plz write another Coordinates\n");
            scanf("%d%d%c",&x,&y,&trash[0],&form);
            if (put_ship(x,y,form,sizeofship,player1)==0) sw=1;
        }
    }
    }
    scanf("%s"&trash);
    for(int i =0;i<nShip;i++)//put && check ship in area for player 2
    {
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);
    if (put_ship(x,y,form,sizeofship,player2)==1)
    {
        int sw=0;
        while (sw==0)
        {
            printf("ship is exist in that area plz write another Coordinates\n");
            scanf("%d%d%c%c",&x,&y,&trash[0],&form);
            if (put_ship(x,y,form,sizeofship,player2)==0) sw=1;
        }
    }
    }
    printTable(pName1 , pName2, player1, player2, areaSize);
    return 0;
}

int main()
{
    int areaSize, x, y, nShip;
    char pName1[21] = {};
    char pName2[21] = {};    
    
    scanf("%i", &areaSize);     //1- size
    scanf("%i", &nShip);        //2- ship amounts
    scanf("%s", pName1);        //3- player1 name
    scanf("%s", pName2);        //4- player2 name
    printTable(pName1 , pName2, player1, player2, areaSize);
    return 0;
}
