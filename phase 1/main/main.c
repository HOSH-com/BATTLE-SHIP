#include <stdio.h>
#include "welcome.h"
#include "printTable.h"

int player1[15][15] = {};   //maximum battle area table is 15*15
int player2[15][15] = {};   

int main()
{
    int nShip;
    char pName1[21] = "FOCP1";
    char pName2[21] = "FOCP2";
    
    scanf("%i", &nShip);
    
    printTable(pName1 , pName2, player1, player2, nShip);
   // printWelcome();
    
    return 0;
    
}
