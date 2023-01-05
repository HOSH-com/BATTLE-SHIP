//main functions:
void new_game_settings();
void start_new_game();
void end_game();

int nShip;

void new_game_settings()
{
    clearScreen();
    //ingredients:
    int x, y, sizeofship=3;
    int i, result;
    char form;
    char trash[40];  

    //in common settings:
    printf("Please enter size of map (3-15):\n");
    scanf("%i", &setting.size_of_area);     //1- area size
    while (setting.size_of_area > 15 || setting.size_of_area < 3)  //check for ERROR
    {
        setTextColor(RED, 15);
        printf("ERROR: ");
        setTextColor(BLACK, 15);
        printf("Enter size of map again (from 3 to 15):\n");
        scanf("%i", &setting.size_of_area);
    }
    setTextColor(BLACK, 15);
    printf("Enter number of ships:\n");
    scanf("%i", &nShip);        //2- ship amounts
    player1[0].number_of_ship = player2[0].number_of_ship = nShip;
    printf("...");
    sleep(3000);
    clearScreen();

    //player 1:
    printf("<PLAYER 1>\n\n"
    "Enter player1 name:\n");
    scanf("%c", &trash[0]);     //getting ready for next "scanf"
    for (i = 0; player1[0].name[i-1] != '\n'; i++)   
    {
        scanf("%c", &player1[0].name[i]);//3- player1 name
    }
    player1[0].name[i-1] = 0;

    //put && check ship in area for player 1:
    for(int i =0;i<nShip;i++)     
    {
        printf("Enter ship position \"%i\" ('row' space 'column' space 'h/v'):\n", i+1);
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);    //4- player1 ships position
        result = put_ship();
        if (result==1 || result==2)  //check for error
        {
            int sw=0;
            while (sw==0)
            {
                if(result == 1)
                {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    printf("Ship exists in this area.\nPlease enter position \"%i\" again ('row' space 'column' space 'h/v'):\n", i+1);
                }
                else if(result == 2)
                {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    printf("The ship is out of the range (the area is %ix%i)."
                    "\nPlease enter position \"%i\" again ('row' space 'column' space 'h/v'):\n", setting.size_of_area, setting.size_of_area ,i+1);
                }
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                result = put_ship();
                if (result==0) sw=1;
            }
        }
    }
    
    printf("Type something then press \"enter\" to continue:\n");
    scanf("%s",&trash);         //5- next player
    clearScreen();

    //player 2:
    printf("<PLAYER 2>\n\n"
    "Enter player2 name:\n");
    scanf("%c", &trash[0]);     //getting ready for next "scanf"
    for (i = 0; player2[0].name[i-1] != '\n'; i++)
    {
        scanf("%c", &player2[0].name[i]);    //6- player2 name
    }
    player2[0].name[i-1] = 0;
 
    //put && check ship in area for player 2:
    for(int i =0;i<nShip;i++)       
    {
        printf("Enter ship position \"%i\" ('row' space 'column' space 'h/v'):\n", i+1);
        scanf("%d%d%c%c",&x,&y,&trash[0],&form);        //7- player2 ships position
        result = put_ship();
        if (result == 1 || result == 2)  //check for error
        {
            int sw=0;
            while (sw==0)
            {
                if(result == 1)
                {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    printf("Ship exists in this area.\nPlease enter position \"%i\" again ('row' space 'column' space 'h/v'):\n", i+1);
                }
                else if(result == 2)
                {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    printf("The ship is out of the range (the area is %ix%i)."
                    "\nPlease enter position \"%i\" again ('row' space 'column' space 'h/v'):\n", setting.size_of_area, setting.size_of_area ,i+1);
                }
                scanf("%d%d%c%c",&x,&y,&trash[0],&form);
                result = put_ship();
                if (result == 0) sw=1;
            }
        }
    }
    printf("...");
    sleep(5000);
}

void start_new_game()
{
    int x, y, result;

    clearScreen();
    //start the new game:
    for (setting.nRound = 1; player1[0].number_of_ship && player2[0].number_of_ship; setting.nRound++)
    {
        printTable(); //1- show PRE-attack table status
        printf("Enter coordinates to shot ('row number' space 'column'):\n"); //2- get the shot coord.
        setTextColor(BLACK,WHITE2);
        scanf("%i %i", &x, &y);      

        switch (setting.nRound % 2)
        {
        //attacker player 1:
        case 1:
            result = fire();
            while (result < 0)   //check for ERRORS
            {
                if (result == -2)
                {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    printf("The ship in this area is damaged already.\n");
                }
                else if (result == -1)
                {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    printf("The shot is out of the range (min=1, max=%i).\n", setting.size_of_area);
                }
                printf("Enter your shot again('row number' space 'column'):\n");
                scanf("%i %i", &x, &y); 
                result = fire();
            }

            if (result == 0 || result == 1 || result==2)     //it's OK
            {
                clearScreen();
                printTable();     //3- show AFTER-attack table status
                if (result==2)
                {
                    printf("One of %s's ships sank!\n", player2[0].name);    //ship SANK
                }
                else if (result==0)
                {
                    player2[0].battlefield[x-1][y-1] = 0;          //DON'T show it in next rounds
                }      
            }
            break;

        //attacker player 2:
        case 0:
            result = fire();
            while (result < 0)   //check for ERRORS
            {
                if (result == -2)
                {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    printf("The ship in this area is damaged already.\n");
                    
                }
                else if (result == -1)
                {
                    setTextColor(RED, 15);
                    printf("ERROR: ");
                    setTextColor(BLACK, 15);
                    printf("The shot is out of the range (min=1, max=%i).\n", setting.size_of_area);
                }
                printf("Enter your shot again('row number' space 'column'):\n");
                setTextColor(BLACK,WHITE2);
                scanf("%i %i", &x, &y); 
                result = fire();
            }

            if (result ==0 || result == 1 || result == 2)     //it's OK
            {
                clearScreen();
                printTable();     //3- show AFTER-attack table status
                if (result==2)
                {
                    printf("One of %s's ships sank!\n", player1[0].name);    //ship SANK
                }
                else if (result==0)                {
                    player1[0].battlefield[x-1][y-1] = 0;          //DON'T show it in next rounds
                }  
            }
            break;
        }
        
        //delay and clearScreen after each round:
        printf("...");
        sleep(5000);
        clearScreen();      
    }

}

void end_game()
{
    if (player1[0].number_of_ship) printf("PLAYER 1 WONNNNNNNNN!"); /*player1 wins*/
    else if (player2[0].number_of_ship) printf("PLAYER 2 WONNNNNNNNN!"); /*player2 wins*/
}

