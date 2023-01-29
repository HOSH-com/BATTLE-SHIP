/*
کتابخانۀ مورد استفاده برای اعمال انجام شده روی فایل‌ها
شامل:...
- خواندن تنظیمات بازی از روی فایل
- ذخیره هر راند بازی درون فایل جهت بازپخش بازی
- پخش بازپخش بازی قبلی
- ذخیره آخرین وضعیت بازی درون فایل جهت ادامۀ بازی قبلی
- خواندن اطلاعات آخرین وضعیت بازی قبلی
*/

#define ESC 27

void file_game_setting();
void file_save_round();
void file_replay();
void save_last_movement_or_last_round();
void read_last_movement_or_last_round();

void file_game_setting()
{   
    clean_battlefields(); // set battlefields to default
    clearScreen();
    int nShip, x, y, result, length, width, height, shipNumber, sw;
    char form, temp[11];
    
    FILE *finput = fopen("input.txt", "rt");
    if (!finput)
    {
        printf("ERROR: can't open the file!\n");
        sleep(5000);
        exit (1);
    }

    fscanf(finput, "%i", &setting.size_of_area); // 1- area size
    fscanf(finput, "%i", &setting.max_element); // 2- element amounts
    player1.remaining_element = player2.remaining_element = setting.max_element;

    
    
    fgets(temp, 2, finput);                 //scaning '\n'
    fgets(player1.name, 100, finput); // 3- p1 name
    length = strlen(player1.name);       //deleting '\n'
    player1.name[length-1] = 0;

    // 4- p1 putting ships:
    shipNumber = 0; // for naming ships
    fscanf(finput, "%i%i%i", &width, &length, &nShip);
    
    player1.remaining_element -= width * length * nShip; // subtract used houses from remainings

    for (int i = 0; i < nShip; ++i)
    {
        fscanf(finput, "%d %d %c", &x, &y, &form);

        // correct user possible misplaced input:
        if ((form == 'h' || form == 'H') && !(length >= width)) 
            intSwap(length, width);

        else if ((form == 'v' || form == 'V') && !(width >= length))
            intSwap(length, width);

        x = x-1; // decrement for initializing battlefields
        y = y-1;

        for (int i = x; i < width + x; ++i)
            for (int j = y; j < length + y; ++j)
                player1.battlefield[i][j] = 100 + shipNumber; 

        // initialize ship coor. array:
        player1.ship_coordinates[shipNumber][0] = x;
        player1.ship_coordinates[shipNumber][1] = y;
        player1.ship_coordinates[shipNumber][2] = length;
        player1.ship_coordinates[shipNumber][3] = width;
        player1.ship_coordinates[shipNumber][4] = form;

        ++player1.number_of_ship;
        ++shipNumber;
    }

    sw = 1;

    while (sw)
    {
        result = 0;

        do // make decision
        {
            fscanf(finput, "%s", temp);

            if (strcmp(temp, "$$$") == 0)
                result = 1;

            else if (strcmp(temp, "---") == 0)
            {
                result = 2;
                sw = 0;
            }    

        } while (!result);

        if (result == 1) // next ship placement
        {
            fscanf(finput, "%i %i %i", &width, &length, &nShip);
            player1.remaining_element -= width * length * nShip; // subtract used houses from remainings

            for (int i = 0; i < nShip; ++i)
            {
                fscanf(finput, "%d %d %c", &x, &y, &form);

                // correct user possible misplaced input:
                if ((form == 'h' || form == 'H') && !(length >= width)) 
                    intSwap(length, width);

                else if ((form == 'v' || form == 'V') && !(width >= length))
                    intSwap(length, width);

                x = x-1; // decrement for initializing battlefields
                y = y-1;

                for (int i = x; i < width + x; ++i)
                    for (int j = y; j < length + y; ++j)
                        player1.battlefield[i][j] = 100 + shipNumber; 

                // initialize ship coor. array:
                player1.ship_coordinates[shipNumber][0] = x;
                player1.ship_coordinates[shipNumber][1] = y;
                player1.ship_coordinates[shipNumber][2] = length;
                player1.ship_coordinates[shipNumber][3] = width;
                player1.ship_coordinates[shipNumber][4] = form;

                ++player1.number_of_ship;
                ++shipNumber;
            }

        }
        
    }
    
    player1.remaining_ship = player1.number_of_ship;

    if (player1.remaining_element < 0) // error
    {
        printf("incorrect inputs!");
        exit(EXIT_FAILURE);
    }



    fgets(temp, 2, finput);                 //scaning '\n'
    fgets(player2.name, 100, finput); // 5- p2 name
    length = strlen(player2.name);       //deleting '\n'
    player2.name[length-1] = 0;

    // 6- p2 putting ships:
    shipNumber = 0; // for naming ships
    fscanf(finput, "%i %i %i", &width, &length, &nShip);
    player2.remaining_element -= width * length * nShip; // subtract used houses from remainings

    for (int i = 0; i < nShip; ++i)
    {
        fscanf(finput, "%d %d %c", &x, &y, &form);

        // correct user possible misplaced input:
        if ((form == 'h' || form == 'H') && !(length >= width)) 
            intSwap(length, width);

        else if ((form == 'v' || form == 'V') && !(width >= length))
            intSwap(length, width);

        x = x-1; // decrement for initializing battlefields
        y = y-1;

        for (int i = x; i < width + x; ++i)
            for (int j = y; j < length + y; ++j)
                player2.battlefield[i][j] = 100 + shipNumber; 

        // initialize ship coor. array:
        player2.ship_coordinates[shipNumber][0] = x;
        player2.ship_coordinates[shipNumber][1] = y;
        player2.ship_coordinates[shipNumber][2] = length;
        player2.ship_coordinates[shipNumber][3] = width;
        player2.ship_coordinates[shipNumber][4] = form;

        ++player2.number_of_ship;
        ++shipNumber;
    }

    sw = 1;

    while (sw)
    {
        result = 0;

        do // make decision
        {
            fscanf(finput, "%s", temp);

            if (strcmp(temp, "$$$") == 0)
                result = 1;

            else if (strcmp(temp, "---") == 0)
            {
                result = 2;
                sw = 0;
            }    

        } while (!result);

        if (result == 1) // next ship placement
        {
            fscanf(finput, "%i %i %i", &width, &length, &nShip);
            player2.remaining_element -= width * length * nShip; // subtract used houses from remainings

            for (int i = 0; i < nShip; ++i)
            {
                fscanf(finput, "%d %d %c", &x, &y, &form);

                // correct user possible misplaced input:
                if ((form == 'h' || form == 'H') && !(length >= width)) 
                    intSwap(length, width);

                else if ((form == 'v' || form == 'V') && !(width >= length))
                    intSwap(length, width);

                x = x-1; // decrement for initializing battlefields
                y = y-1;

                for (int i = x; i < width + x; ++i)
                    for (int j = y; j < length + y; ++j)
                        player2.battlefield[i][j] = 100 + shipNumber; 

                // initialize ship coor. array:
                player2.ship_coordinates[shipNumber][0] = x;
                player2.ship_coordinates[shipNumber][1] = y;
                player2.ship_coordinates[shipNumber][2] = length;
                player2.ship_coordinates[shipNumber][3] = width;
                player2.ship_coordinates[shipNumber][4] = form;

                ++player2.number_of_ship;
                ++shipNumber;
            }

        }
        
    }
    
    player2.remaining_ship = player2.number_of_ship;

    if (player2.remaining_element < 0) // error
    {
        printf("incorrect inputs!");
        exit(EXIT_FAILURE);
    }


    fscanf(finput, "%i", &setting.max_repair);
    player1.remaining_repair = player2.remaining_repair = setting.max_repair;

    result = fclose(finput);
    if (result == EOF)
    {
        printf("ERROR: can't close the file\n");
        sleep(5000);
        exit (1);
    }
}

void file_save_round()
{
    FILE *fround;

    fround = fopen("replay.dat", "ab");
    if (!fround)
    {
        printf("ERROR: can't open replay.dat\n");
        exit (-1);
    }
    fwrite(&setting, sizeof(GAME_SETTING), 1, fround);
    fwrite(&player1, sizeof(PLAYERS_INFO), 1, fround);
    fwrite(&player2, sizeof(PLAYERS_INFO), 1, fround);
    fclose(fround);
    
}

void file_replay()
{
    int sw = 1;
    char choice;
    FILE* freplay = fopen("replay.dat", "rb");
    if (!freplay)
    {
        printf("ERROR: can't open replay.dat\n");
        exit (-1);
    }

    clearScreen();
    fread(&setting, sizeof(GAME_SETTING), 1, freplay);
    fread(&player1, sizeof(PLAYERS_INFO), 1, freplay);
    fread(&player2, sizeof(PLAYERS_INFO), 1, freplay);

    //check if there is not any recorded match:
    if (setting.nRound == 0)
    {
        clearScreen();
        printf("\n\n\n          THERE IS NOTHING TO BE REPLAYED.\n          Returning to menu...\n");
        sleep(5000);
        return;
    }
    
    printTable();
    printf("\n\nPrevious[P], Next[N], End[E], Back[ESCAPE]\n");
    do
    {
        do
        {
            choice = getch();
        } while (choice != 'P'&& choice != 'N'&& choice != 'E'&&choice != 'p'&& choice != 'n'&& choice != 'e'&& choice != ESC);

        switch (choice)
        {
        case 'p':
        case 'P':
            if (ftell(freplay) > sizeof(LAST_ROUND))
            {
                clearScreen();
                fseek(freplay, -2*sizeof(LAST_ROUND), SEEK_CUR);
                fread(&setting, sizeof(GAME_SETTING), 1, freplay);
                fread(&player1, sizeof(PLAYERS_INFO), 1, freplay);
                fread(&player2, sizeof(PLAYERS_INFO), 1, freplay);
                printTable();
                printf("\n\nPrevious[P], Next[N], End[E], Back[ESCAPE]\n");
            }
            break;
        
        case 'n':
        case 'N':
            fread(&setting, sizeof(GAME_SETTING), 1, freplay);  //extra
            if (feof(freplay))
                sw = 0;
            else
            {
                fseek(freplay, -1*sizeof(GAME_SETTING), SEEK_CUR);  
                clearScreen();
                fread(&setting, sizeof(GAME_SETTING), 1, freplay);
                fread(&player1, sizeof(PLAYERS_INFO), 1, freplay);
                fread(&player2, sizeof(PLAYERS_INFO), 1, freplay);
                printTable();
                printf("\n\nPrevious[P], Next[N], End[E], Back[ESCAPE]\n");
            }
            break;
        
        case 'e':
        case 'E':
            clearScreen();
            fseek(freplay, -sizeof(LAST_ROUND), SEEK_END);
            fread(&setting, sizeof(GAME_SETTING), 1, freplay);
            fread(&player1, sizeof(PLAYERS_INFO), 1, freplay);
            fread(&player2, sizeof(PLAYERS_INFO), 1, freplay);
            printTable();
            printf("\n\nPrevious[P], Next[N], End[E], Back[ESCAPE]\n");
            break;
        
        case ESC:
            sw = 0;
            break;
        }
        
    } while (sw == 1);
    
    fclose(freplay);
}

void save_last_movement_or_last_round()
{
    FILE *openfile=fopen("continue.dat","wb");
    if (!openfile)
    {
        printf("ERROR:We cant open save FILE");
        exit (-1);
    }
    fwrite(&setting,sizeof(GAME_SETTING),1,openfile);
    fwrite(&player1,sizeof(PLAYERS_INFO),1,openfile);
    fwrite(&player2,sizeof(PLAYERS_INFO),1,openfile);
    fclose(openfile);
}

void read_last_movement_or_last_round()
{
    FILE *openfile=fopen("continue.dat","rb");
    if (!openfile)
    {
        printf("ERROR:We cant open save FILE");
        exit (-1);
    }
    fread(&setting,sizeof(GAME_SETTING),1,openfile);
    fread(&player1,sizeof(PLAYERS_INFO),1,openfile);
    fread(&player2,sizeof(PLAYERS_INFO),1,openfile);
    fclose(openfile);
}