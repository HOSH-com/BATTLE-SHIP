#include <stdio.h>

#define NO_SHIP 0
#define DESTROYED -1

int tedad_char(const char p1[]);

void printTable(const char pName1[], const char pName2[], const int player1[][15], const int player2[][15], int n)
{
    /*  HESAM   code:    */

    int L1=tedad_char(pName1);//tedad character pName1
    int L2=tedad_char(pName2);//tedad character pName2
    int e=15;//space between arrays
    for (int i = 0; i <3+(3*n+L1)/2 - 6; i++)//print space befor pName1
    {
        printf(" ");
    }
    printf("%s",pName1);
    for (int i = 0; i <3*(n+1)-(L1+L2)/2+14; i++)//print space between pName1 and pName2
    {
         printf(" ");
    }
    printf("%s\n",pName2);
    for (int i = 0; i <4*n+18 ; i++)
    {
         printf("_");
    }
    printf("\n");




    /*  REZA code:  */


    //printing table:

        //first line:
            printf("   ");                        //section 1: empty space 1
            for (int i = 1; i <= 9 && i <= n; i++) {      //section 2: col nom 1
                printf ("%i  ", i);
            }
            for (int i = 10; i <= n; i++) {      //section 2: col nom 1
                printf ("%i ", i);
            }
            printf ("      |          ");                  //section 3: empty space 2
            for (int i = 1; i <= 9 && i <= n; i++) {      //section 4: col nom 2
                printf ("%i  ", i);
            }
            for (int i = 10; i <= n; i++) {      //section 4: col nom 2
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
                        /*default:
                            break;*/
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
                        /*default:
                            break;*/
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
                        /*default:
                            break;*/
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
                        /*default:
                            break;*/
                    }
                }
                printf("\n");       //next line
            }  
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