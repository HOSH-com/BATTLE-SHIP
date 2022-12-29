/*
کتابخانۀ مورد استفاده برای چاپ جدول
شامل:...
- نام بازیکنان
- میدان نبرد
- تعداد کشتی‌های باقی مانده

*/

#include <stdio.h>

#define NO_SHIP 0
#define MISSED -1

int tedad_char(const char p1[]);
void printNames(const char pName1[], const char pName2[], int n, int nRound);
void printBattlefields(const int player1[][15], const int player2[][15], int n, int nRound);
void printRemainingShips(int n, int p1_remainingShips, int p2_remainingShips);
void printTable(const char pName1[], const char pName2[], const int player1[][15], const int player2[][15], int n, int nRound, int p1_remainingShips, int p2_remainingShips);

void printTable(const char pName1[], const char pName2[], const int player1[][15], const int player2[][15], int areaSize, int nRound, int p1_remainingShips, int p2_remainingShips)
{
    //printing players name:
    printNames(pName1, pName2, areaSize, nRound);

    //printing players battlefield:
    printBattlefields(player1, player2, areaSize, nRound);

    //printing remaining ships:
    printRemainingShips(areaSize, p1_remainingShips, p2_remainingShips);
}

int tedad_char(const char p1[])
{
    for (int i = 0; i < 50; i++)
    {
        if (p1[i]=='\0')
        {
            return i;
        }
    }
    return 3;
}

//functions declaratoin:

void printNames(const char pName1[], const char pName2[], int areaSize, int nRound)
{
    int L1=tedad_char(pName1);//tedad character pName1
    int L2=tedad_char(pName2);//tedad character pName2
    int e=15;//space between arrays

    switch (nRound % 2)
    {
    //attacker player 1:
    case 1:
        for (int i = 0; i <(3+(3*areaSize-L1)/2); i++)//section 1: print space befor pName1
        {
            printf(" ");
        }
        printf("*%s",pName1);    //section 2: player1 name
        for (int i = 0; i <3*(areaSize+1)-(L1+L2)/2+15; i++)//section 3: print space between pName1 and pName2
        {
            printf(" ");
        }
        printf("%s\n",pName2);  //section 4: player2 name
        for (int i = 0; i <6*(areaSize+1)+14 ; i++)
        {
            printf("=");    //section 5: seperating names from battlefields
        }
        printf("\n");   //section 6: next line
        break;
    
    //attacker player 2:
    case 0:
        for (int i = 0; i <(3+(3*areaSize-L1)/2); i++)     //section 1: print space befor pName1
        {
            printf(" ");
        }
        printf("%s",pName1);        //section 2: player1 name
        for (int i = 0; i <3*(areaSize+1)-(L1+L2)/2+15; i++)//section 3: print space between pName1 and pName2
        {
            printf(" ");
        }
        printf("*%s\n",pName2);      //section 4: player2 name
        for (int i = 0; i <6*(areaSize+1)+14 ; i++)
        {
            printf("=");    //section 5: seperating names from battlefields
        }
        printf("\n");       //section 6: next line
        break;
    }
}

void printBattlefields(const int player1[][15], const int player2[][15], int areaSize, int nRound)
{
    switch (nRound % 2)
    {
    //attacker player 1:
    case 1:
        //first line:
        printf("   ");                                 //section 1: empty space 1
        for (int i = 1; i <= areaSize; i++) {      //section 2: col nom 1
            printf ("%2i ", i);
        }
        printf ("       |          ");                  //section 3: empty space 2
        for (int i = 1; i <= areaSize; i++) {      ////section 4: col nom 2
            printf ("%2i ", i);
        }    
        printf("\n");                        //next line
    
        //other lines:
        for (int i = 0; i < areaSize; i++)             //main loop with new condition
        {
            printf("%2i  ", i+1);               //section 1: row nom 1
            for (int j = 0; j < areaSize; j++)      //section 2: player 1
            {
                switch (player1[i][j]) 
                {
                case NO_SHIP:
                    printf("~  "); 
                    break;
                default:
                    if (player1[i][j] >= 1000) printf("O  ");    //show ship
                    if (player1[i][j] <= -1000) printf("Y  ");     //show damaged ship 
                        break;
                }
            }
            printf("      |       ");               //section 3: empty space
            printf("%2i  ", i+1);                     //section 4: row nom 2
            for (int j = 0; j < areaSize; j++)            //section 5: player 2
            {   
                switch (player2[i][j]) 
                {
                case NO_SHIP:
                    printf("~  "); 
                    break;
                case MISSED:
                    printf("X  "); 
                    break;
                default:
                    if (player2[i][j] >= 1000) printf("~  ");    //DON'T show ships!
                    if (player2[i][j] <= -1000) printf("Y  ");     //show damaged ships 
                    break;
                }
            }
            printf("\n");       //next line
        }
        break;
    
    //attacker player 2:
    case 0:
        //first line:
        printf("   ");                                 //section 1: empty space 1
        for (int i = 1; i <= areaSize; i++) {      //section 2: col nom 1
            printf ("%2i ", i);
        }
        printf ("       |          ");                  //section 3: empty space 2
        for (int i = 1; i <= areaSize; i++) {      ////section 4: col nom 2
            printf ("%2i ", i);
        }    
        printf("\n");                        //next line
    
        //other lines:
        for (int i = 0; i < areaSize; i++)             //main loop with new condition
        {
            printf("%2i  ", i+1);               //section 1: row nom 1
            for (int j = 0; j < areaSize; j++)      //section 2: player 1
            {
                switch (player1[i][j]) 
                {
                case NO_SHIP:
                    printf("~  "); 
                    break;
                case MISSED:
                    printf("X  "); 
                    break;
                default:
                    if (player1[i][j] >= 1000) printf("~  ");    //DON'T show ships!
                    if (player1[i][j] <= -1000) printf("Y  ");     //show damaged ships 
                    break;
                }
            }
            printf("      |       ");               //section 3: empty space
            printf("%2i  ", i+1);                     //section 4: row nom 2
            for (int j = 0; j < areaSize; j++)            //section 5: player 2
            {   
                switch (player2[i][j]) 
                {
                case NO_SHIP:
                    printf("~  "); 
                    break;
                default:
                    if (player2[i][j] >= 1000) printf("O  ");    //show ship
                    if (player2[i][j] <= -1000) printf("Y  ");     //show damaged ship 
                        break;
                }
            }
            printf("\n");       //next line
        }
        break;
    }
}

void printRemainingShips(int areaSize, int p1_remainingShips, int p2_remainingShips)
{
    printf("\n");
    printf("remaining ships: %i", p1_remainingShips);
        for (int i = 0; i <3*(areaSize+1)+14-18; i++)
    {
    printf(" ");
    }  
    printf("remaining ships: %i\n", p2_remainingShips);
    for (int i = 0; i <6*(areaSize+1)+14 ; i++)
        {
            printf("=");    
        }
    printf("\n\n");
}