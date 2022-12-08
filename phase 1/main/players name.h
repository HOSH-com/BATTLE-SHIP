#include <stdio.h>
int tedad_char(char p1[])
{
    for (int i = 0;; i++)
    {
        if (p1[i]=='\0')
        {
            return i-1;
        }
    }
}
void pNames (char pName1[], char pName2[],int n )
{
    int L1=tedad_char(pName1);//tedad character pName1
    int L2=tedad_char(pName2);//tedad character pName2
    int e=15;//space between arrays
    for (int i = 0; i < ((2*n+1)/2)-L1/2; i++)//print space befor pName1
    {
        printf(" ");
    }
    printf("%s",pName1);
    for (int i = 0; i <(((2*n+1)+e)+2*n+1)/2-(L2/2); i++)//print space between pName1 and pName2
    {
         printf(" ");
    }
    printf("%s\n",pName2);
    for (int i = 0; i <4*n+17 ; i++)
    {
         printf("-");
    }
    printf("\n");
    
}