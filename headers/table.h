#include <stdio.h>

#define NO_SHIP 0
#define DESTROYED -1

int tedad_char(const char p1[]);
void printNames(const char pName1[], const char pName2[], int n);
void printBattlefields(const int player1[][15], const int player2[][15], int n);
void printRemainingShips(int n);

void printTable(const char pName1[], const char pName2[], const int player1[][15], const int player2[][15], int n)
{
    //printing players name:
    printNames(pName1, pName2, n);

    //printing players battlefield:
    printBattlefields(player1, player2, n);

    //printing remaining ships:
    printRemainingShips(n);
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
}

//functions declaratoin:

void printNames(const char pName1[], const char pName2[], int n)
{
    int L1=tedad_char(pName1);//tedad character pName1
    int L2=tedad_char(pName2);//tedad character pName2
    int e=15;//space between arrays
    for (int i = 0; i <(3+(3*n-L1)/2) - 1; i++)//print space befor pName1
    {
        printf(" ");
    }
    printf("%s",pName1);
    for (int i = 0; i <3*(n+1)-(L1+L2)/2+14; i++)//print space between pName1 and pName2
    {
         printf(" ");
    }
    printf("%s\n",pName2);
    for (int i = 0; i <6*(n+1)+13 ; i++)
    {
         printf("=");
    }
    printf("\n");
}

void printBattlefields(const int player1[][15], const int player2[][15], int n)
{
    //first line:
        printf("   ");                                 //section 1: empty space 1
        for (int i = 1; i <= 9 && i <= n; i++) {      //section 2: col nom 1
            printf ("%i  ", i);
        }
        for (int i = 10; i <= n; i++) {      //...
            printf ("%i ", i);
        }
        printf ("      |          ");                  //section 3: empty space 2
        for (int i = 1; i <= 9 && i <= n; i++) {      //section 4: col nom 2
            printf ("%i  ", i);
        }
        for (int i = 10; i <= n; i++) {      //...
            printf ("%i ", i);
        }    
        printf("\n");                        //next line
    
    //other lines:
        for (int i = 0; i < 9 && i < n; i++)              //main loop
        {
            printf("%i  ", i+1);               //section 1: row nom 1
            for (int j = 0; j < n; j++)       //section 2: player 1
            {
                switch (player1[i][j]) 
                {
                    case NO_SHIP:
                        printf("~  "); 
                        break;
                    case DESTROYED:
                        printf("X  "); 
                        break;
                    default:
                        if(player1[i][j] > 0) printf("■  ");
                        break;
                }
            }
            printf("      |       ");               //section 3: empty space
            printf("%i  ", i+1);                    //section 4: row nom 1
            for (int j = 0; j < n; j++)            //section 5: player 2
            {   
                switch (player2[i][j]) {
                    case NO_SHIP:
                        printf("~  "); 
                        break;
                    case DESTROYED:
                        printf("X  "); 
                        break;
                    default:
                        if(player2[i][j] > 0) printf("■  ");
                        break;
                }
            }
            printf("\n");       //next line
        }
        //resume:
        for (int i = 9; i < n; i++)             //main loop with new condition
        {
            printf("%i ", i+1);               //section 1: row nom 1
            for (int j = 0; j < n; j++)      //section 2: player 1
            {
                switch (player1[i][j]) 
                {
                    case NO_SHIP:
                        printf("~  "); 
                        break;
                    case DESTROYED:
                        printf("X  "); 
                        break;
                    default:
                        if(player1[i][j] > 0) printf("■  ");
                        break;
                }
            }
            printf("      |       ");               //section 3: empty space
            printf("%i ", i+1);                     //section 4: row nom 1
            for (int j = 0; j < n; j++)            //section 5: player 2
            {   
                switch (player2[i][j]) {
                    case NO_SHIP:
                        printf("~  "); 
                        break;
                    case DESTROYED:
                        printf("X  "); 
                        break;
                    default:
                        if(player2[i][j] > 0) printf("■  ");
                        break;
                }
            }
            printf("\n");       //next line
        }
}

void printRemainingShips(int n)
{
    printf("\n");
    printf("remaining ships: 3");
        for (int i = 0; i <3*(n+1)+14-18; i++)
    {
    printf(" ");
    }  
    printf("remaining ships: 3");
}