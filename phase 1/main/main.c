#include <stdio.h>
#include "welcome.h"
#include "printTable.h"

int player1[15][15] = {};   //maximum battle area table is 15*15
int player2[15][15] = {};   

int main()
{

    char pName1, pName2;
    pName1 = 'a';
    pName2 = 'b';
    
    printTable(pName1 , pName2, player1, player2, 5);
    
    
    return 0;
    
}
