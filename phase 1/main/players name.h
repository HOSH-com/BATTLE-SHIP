#include <stdio.h>
int tedad_char(char p1[])
{
    for (int i = 0;; i++)
    {
        if (p1[i]=='\0')
        {
            return i;
        }
    }
}
void pNames (char p1[], char p2[],int n )
{
    int L1=tedad_char(p1);//tedad character p1
    int L2=tedad_char(p2);//tedad character p2
    int e=15;//space between arrays
    for (int i = 0; i < ((2*n+1)/2)-L1/2; i++)//print space befor p1
    {
        printf(" ");
    }
    printf("%s",p1);
    for (int i = 0; i <(((2*n+1)+e)+2*n+1)/2-(L2/2); i++)//print space between p1 and p2
    {
         printf(" ");
    }
    printf("%d",p2);
}