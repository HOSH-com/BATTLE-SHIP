/*
کتابخانۀ مورد استفاده برای چاپ جدول
شامل:...
- نام بازیکنان
- میدان نبرد
- تعداد کشتی‌های باقی مانده

*/

//constants:
#define NO_SHIP 0
#define MISSED -1
#define NAME_LIMIT 50

//tools:


//main functions:
void printNames();
void printBattlefields();
void printRemainingShips();
void printTable();


//functions definitions:
void printTable()
{
    //printing players name:
    printNames();

    //printing players battlefield:
    printBattlefields();

    //printing remaining ships:
    printRemainingShips();
}

void printNames()
{
    int L1 = tedad_char(player1.name);//tedad character pName1
    int L2 = tedad_char(player2.name);//tedad character pName2
    int e = 15;//space between arrays

    switch (setting.nRound % 2)
    {
    //attacker player 1:
    case 1:
        for (int i = 0; i <(3+(3*setting.size_of_area-L1)/2); i++)//1- print space befor pName1
        {
            printf(" ");
        }
        printf("*%s",player1.name);    //2- player1 name
        for (int i = 0; i <3*(setting.size_of_area+1)-(L1+L2)/2+15; i++)//3- print space between pName1 and pName2
        {
            printf(" ");
        }
        printf("%s\n",player2.name);  //4- player2 name
        for (int i = 0; i <6*(setting.size_of_area+1)+14 ; i++)
        {
            printf("=");    //5- seperating names from battlefields
        }
        printf("\n");   //6- next line
        break;
    
    //attacker player 2:
    case 0:
        for (int i = 0; i <(3+(3*setting.size_of_area-L1)/2); i++)     //1- print space befor pName1
        {
            printf(" ");
        }
        printf("%s",player1.name);        //2- player1 name
        for (int i = 0; i <3*(setting.size_of_area+1)-(L1+L2)/2+14; i++)//3- print space between pName1 and pName2
        {
            printf(" ");
        }
        printf("*%s\n",player2.name);      //4- player2 name
        for (int i = 0; i <6*(setting.size_of_area+1)+14 ; i++)
        {
            printf("=");    //5- seperating names from battlefields
        }
        printf("\n");       //next line
        break;
    }
}

void printBattlefields()
{
    switch (setting.nRound % 2)
    {
    //attacker player 1:
    case 1:
        //first line:
        printf("   ");                                 //1- empty space before p1
        for (int i = 1; i <= setting.size_of_area; i++) {      //2- col. num. p1
            printf ("%2i ", i);
        }
        printf ("       |          ");                  //3- seperating p1 from p2
        for (int i = 1; i <= setting.size_of_area; i++) {      //4- col. num. p2
            printf ("%2i ", i);
        }    
        printf("\n");                        //next line
    
        //other lines:
        for (int i = 0; i < setting.size_of_area; i++)
        {
            printf("%2i  ", i+1);               //1- row num. p1
            for (int j = 0; j < setting.size_of_area; j++)      //2- player1 battlefield
            {
                switch (player1.battlefield[i][j]) 
                {
                case NO_SHIP:
                    setTextColor(BLUE,WHITE2);
                    printf("~  "); 
                    setTextColor(BLACK,WHITE2);
                    break;
                default:
                    if (player1.battlefield[i][j] >= 1000) printf("%c  ", 254);    //show SHIPS
                    if (player1.battlefield[i][j] <= -1000) printf("X  ");     //show DAMAGED ships
                        break;
                }
            }
            printf("      |       ");               //3- seperating p1 from p2
            printf("%2i  ", i+1);                     //4- row num. p2
            for (int j = 0; j < setting.size_of_area; j++)            //5- player2 battlefield
            {   
                switch (player2.battlefield[i][j]) 
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
                    if (player2.battlefield[i][j] >= 1000)
                    {
                        setTextColor(BLUE,WHITE2);
                        printf("~  ");    //DON'T show ships!
                        setTextColor(BLACK,WHITE2); 
                    }
                    if (player2.battlefield[i][j] <= -1000) printf("X  ");     //show DAMAGED ships 
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
        for (int i = 1; i <= setting.size_of_area; i++) {      //2- col. num. p1
            printf ("%2i ", i);
        }
        printf ("       |          ");                  //3- empty space before p2
        for (int i = 1; i <= setting.size_of_area; i++) {      //4- col. num. p2
            printf ("%2i ", i);
        }    
        printf("\n");                        //next line

        //other lines:
        for (int i = 0; i < setting.size_of_area; i++)
        {
            printf("%2i  ", i+1);               //1- row num. p1
            for (int j = 0; j < setting.size_of_area; j++)      //2- player1 battlefield
            {
                switch (player1.battlefield[i][j]) 
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
                    if (player1.battlefield[i][j] >= 1000)
                    {
                        setTextColor(BLUE,WHITE2);
                        printf("~  ");    //DON'T show ships!
                        setTextColor(BLACK,WHITE2); 
                    }
                    if (player1.battlefield[i][j] <= -1000) printf("X  ");     //show DAMAGED ships 
                    break;
                }
            }
            printf("      |       ");               //3- seperating p1 from p2
            printf("%2i  ", i+1);                     //4- row num. p2
            for (int j = 0; j < setting.size_of_area; j++)            //5- player2 battlefield
            {   
                switch (player2.battlefield[i][j]) 
                {
                case NO_SHIP:
                    setTextColor(BLUE,WHITE2);
                    printf("~  "); 
                    setTextColor(BLACK,WHITE2);
                    break;
                default:
                    if (player2.battlefield[i][j] >= 1000) printf("%c  ", 254);    //show SHIPS
                    if (player2.battlefield[i][j] <= -1000) printf("X  ");     //show DAMAGED ships 
                        break;
                }
            }
            printf("\n");       //next line
        }
        break;
    }
}

void printRemainingShips()
{
    printf("\n");       //1- seperating it from last function

    printf(" remaining ships: %i", player1.remaining_ship);   //2- p1 remainings
    for (int i = 0; i <3*(setting.size_of_area+1)-3; i++)       //3- empty spaces before p2
    {
        printf(" ");
    }  
    printf("remaining ships: %i\n", player2.remaining_ship); //4- p2 remainings
    for (int i = 0; i <6*(setting.size_of_area+1)+14 ; i++)         //5- seperating it from incomings 
    {
        printf("=");    
    }

    printf("\n\n"); //6- next line and 5)...
}
