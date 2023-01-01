/*
کتابخانۀ مورد استفاده برای چاپ جدول
شامل:...
- نام بازیکنان
- میدان نبرد
- تعداد کشتی‌های باقی مانده

*/

#include <stdio.h>


#define BLACK 0
#define BLUE 3
#define RED 4
#define WHITE1 7
#define WHITE2 15

//constants:
#define NO_SHIP 0
#define MISSED -1
#define NAME_LIMIT 50

//tools:
int tedad_char(const char p1[]);

//main functions:
void printNames(const char pName1[], const char pName2[], int n, int nRound);
void printBattlefields(const int player1[][15], const int player2[][15], int n, int nRound);
void printRemainingShips(int n, int p1_remainingShips, int p2_remainingShips);
void printTable(const char pName1[], const char pName2[], const int player1[][15], const int player2[][15], int n, int nRound, int p1_remainingShips, int p2_remainingShips);
void setTextColor(int textColor, int backColor);

//functions definitions:
void printTable(const char pName1[], const char pName2[], const int player1[][15], const int player2[][15], int areaSize, int nRound, int p1_remainingShips, int p2_remainingShips)
{
    //printing players name:
    printNames(pName1, pName2, areaSize, nRound);

    //printing players battlefield:
    printBattlefields(player1, player2, areaSize, nRound);

    //printing remaining ships:
    printRemainingShips(areaSize, p1_remainingShips, p2_remainingShips);
}

int tedad_char(const char pName[])
{
    for (int i = 0; i < NAME_LIMIT; i++)
    {
        if (pName[i]=='\0')
        {
            return i;   //name SIZE (i)
        }
    }
    return -1;      //name limit exeeded ERROR (-1)
}

void printNames(const char pName1[], const char pName2[], int areaSize, int nRound)
{
    int L1 = tedad_char(pName1);//tedad character pName1
    int L2 = tedad_char(pName2);//tedad character pName2
    int e = 15;//space between arrays

    switch (nRound % 2)
    {
    //attacker player 1:
    case 1:
        for (int i = 0; i <(3+(3*areaSize-L1)/2); i++)//1- print space befor pName1
        {
            printf(" ");
        }
        printf("*%s",pName1);    //2- player1 name
        for (int i = 0; i <3*(areaSize+1)-(L1+L2)/2+15; i++)//3- print space between pName1 and pName2
        {
            printf(" ");
        }
        printf("%s\n",pName2);  //4- player2 name
        for (int i = 0; i <6*(areaSize+1)+14 ; i++)
        {
            printf("=");    //5- seperating names from battlefields
        }
        printf("\n");   //6- next line
        break;
    
    //attacker player 2:
    case 0:
        for (int i = 0; i <(3+(3*areaSize-L1)/2); i++)     //1- print space befor pName1
        {
            printf(" ");
        }
        printf("%s",pName1);        //2- player1 name
        for (int i = 0; i <3*(areaSize+1)-(L1+L2)/2+15; i++)//3- print space between pName1 and pName2
        {
            printf(" ");
        }
        printf("*%s\n",pName2);      //4- player2 name
        for (int i = 0; i <6*(areaSize+1)+14 ; i++)
        {
            printf("=");    //5- seperating names from battlefields
        }
        printf("\n");       //next line
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
        printf("   ");                                 //1- empty space before p1
        for (int i = 1; i <= areaSize; i++) {      //2- col. num. p1
            printf ("%2i ", i);
        }
        printf ("       |          ");                  //3- seperating p1 from p2
        for (int i = 1; i <= areaSize; i++) {      //4- col. num. p2
            printf ("%2i ", i);
        }    
        printf("\n");                        //next line
    
        //other lines:
        for (int i = 0; i < areaSize; i++)
        {
            printf("%2i  ", i+1);               //1- row num. p1
            for (int j = 0; j < areaSize; j++)      //2- player1 battlefield
            {
                switch (player1[i][j]) 
                {
                case NO_SHIP:
                    setTextColor(BLUE,WHITE2);
                    printf("~  "); 
                    setTextColor(BLACK,WHITE2);
                    break;
                default:
                    if (player1[i][j] >= 1000) printf("%c  ", 254);    //show SHIPS
                    if (player1[i][j] <= -1000) printf("X  ");     //show DAMAGED ships
                        break;
                }
            }
            printf("      |       ");               //3- seperating p1 from p2
            printf("%2i  ", i+1);                     //4- row num. p2
            for (int j = 0; j < areaSize; j++)            //5- player2 battlefield
            {   
                switch (player2[i][j]) 
                {
                case NO_SHIP:
                    setTextColor(BLUE,WHITE2);
                    printf("~  "); 
                    setTextColor(BLACK,WHITE2);
                    break;
                case MISSED:
                    printf("%c  ", 168); 
                    break;
                default:
                    if (player2[i][j] >= 1000)
                    {
                        setTextColor(BLUE,WHITE2);
                        printf("~  ");    //DON'T show ships!
                        setTextColor(BLACK,WHITE2); 
                    }
                    if (player2[i][j] <= -1000) printf("X  ");     //show DAMAGED ships 
                    break;
                }
            }
            printf("\n");       //next line
        }
        break;
    
    //attacker player 2:
    case 0:
        //first line:
        printf("   ");                                 //1- seperating p1 from p2
        for (int i = 1; i <= areaSize; i++) {      //2- col. num. p1
            printf ("%2i ", i);
        }
        printf ("       |          ");                  //3- empty space before p2
        for (int i = 1; i <= areaSize; i++) {      //4- col. num. p2
            printf ("%2i ", i);
        }    
        printf("\n");                        //next line

        //other lines:
        for (int i = 0; i < areaSize; i++)
        {
            printf("%2i  ", i+1);               //1- row num. p1
            for (int j = 0; j < areaSize; j++)      //2- player1 battlefield
            {
                switch (player1[i][j]) 
                {
                case NO_SHIP:
                    setTextColor(BLUE,WHITE2);
                    printf("~  ");
                    setTextColor(BLACK,WHITE2); 
                    break;
                case MISSED:
                    printf("%c  ", 168); 
                    break;
                default:
                    if (player1[i][j] >= 1000)
                    {
                        setTextColor(BLUE,WHITE2);
                        printf("~  ");    //DON'T show ships!
                        setTextColor(BLACK,WHITE2); 
                    }
                    if (player1[i][j] <= -1000) printf("X  ");     //show DAMAGED ships 
                    break;
                }
            }
            printf("      |       ");               //3- seperating p1 from p2
            printf("%2i  ", i+1);                     //4- row num. p2
            for (int j = 0; j < areaSize; j++)            //5- player2 battlefield
            {   
                switch (player2[i][j]) 
                {
                case NO_SHIP:
                    setTextColor(BLUE,WHITE2);
                    printf("~  "); 
                    setTextColor(BLACK,WHITE2);
                    break;
                default:
                    if (player2[i][j] >= 1000) printf("%c  ", 254);    //show SHIPS
                    if (player2[i][j] <= -1000) printf("X  ");     //show DAMAGED ships 
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
    printf("\n");       //1- seperating it from last function

    printf("remaining ships: %i", p1_remainingShips);   //2- p1 remainings
    for (int i = 0; i <3*(areaSize+1)-2; i++)       //3- empty spaces before p2
    {
        printf(" ");
    }  
    printf("remaining ships: %i\n", p2_remainingShips); //4- p2 remainings
    for (int i = 0; i <6*(areaSize+1)+14 ; i++)         //5- seperating it from incomings 
    {
        printf("=");    
    }

    printf("\n\n"); //6- next line and 5)...
}
void setTextColor(int textColor, int backColor)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);
}
