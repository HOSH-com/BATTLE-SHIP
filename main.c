#include <stdio.h>
#include <string.h>
#include "headers/welcome.h"
#include "headers/table.h"
#include "headers/ship.h"

int player1[15][15] = {};   //maximum battle area table is 15*15
int player2[15][15] = {};   

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
