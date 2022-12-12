#include <stdio.h>
#include "welcome.h"
#include "printTable.h"
#include "fire.h"

int player1[15][15] = {};   //maximum battle area table is 15*15
int player2[15][15] = {};   

int main()
{
    int nShip,x,y;
    char pName1[21] = "FOCP1";
    char pName2[21] = "FOCP2";
    
    scanf("%i", &nShip);
    for(int i =0;i<3;i++)
    {
        scanf("%d%d",&x,&y);
        fire(x,y,player2);
        fire(x,y,player1);
    }
    printTable(pName1 , pName2, player1, player2, nShip);
   // printWelcome();
    return 0;
}
