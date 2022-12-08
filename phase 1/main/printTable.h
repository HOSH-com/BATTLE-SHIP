#include <stdio.h>

#define NO_SHIP 0
#define DESTROYED -1

void printTable(char pName1, char pName2, int player1[][15], int player2[][15], int n)
{
    /*  HESAM   code:    */






    /*  REZA code:  */


    //printing:

        //first line:
            printf("  ");                        //section 1: empty space 1

            for (int i = 1; i <= n; i++) {      //section 2: col nom 1
                printf ("%i ", i);
            }
            printf ("\b\t|\t  ");                  //section 3: empty space 2

            for (int i = 1; i <= n; i++) {      //section 4: col nom 2
                printf ("%i ", i);
            }
            printf("\n");                        //next line
        
        //other lines:
            for (int i = 0; i < n; i++) {    //main loop
        
                printf("%i ", i+1);               //section 1: row nom 1

                for (int j = 0; j < n; j++){    //section 2: player 1

                    switch (player1[i][j]) {
                        case NO_SHIP:
                            printf("~ "); 
                            break;
                        case DESTROYED:
                            printf("X "); 
                            break;
                        /*default:
                            break;*/
                    }
                }
                printf("\b\t|\t");               //section 3: empty space

                for (int j = 0; j < n; j++){    //section 4: player 2
                   
                    switch (player2[i][j]) {
                        case NO_SHIP:
                            printf("~ "); 
                            break;
                        case DESTROYED:
                            printf("X "); 
                            break;
                        /*default:
                            break;*/
                    }
                }
                printf("\n");       //next line
            }
    
}