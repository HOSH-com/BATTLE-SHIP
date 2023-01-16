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
    clean_battlefields();
    clearScreen();
    int nShip, x, y, result, length;
    char form, temp[11];
    FILE *finput = fopen("input.txt", "rt");
    if (!finput)
    {
        printf("ERROR: can't open the file!\n");
        sleep(5000);
        exit (1);
    }
    fscanf(finput, "%i", &setting.size_of_area);
    fscanf(finput, "%i", &player1.number_of_ship);
    nShip = player1.remaining_ship = player2.remaining_ship = player2.number_of_ship = player1.number_of_ship;

    fgets(temp, 2, finput);                 //scaning '\n'
    fgets(player1.name, 100, finput);     
    length = strlen(player1.name);       //deleting '\n'
    player1.name[length-1] = 0;

    //putting ships for player1:
    for (int i = 0; i < nShip; i++)
    {
        fscanf(finput, "%i %i %c", &x, &y, &form);    
        x--; y--;
        if (form=='H' || form=='h')     //Horizental
        {
            for (int j = 0; j < sizeofship; j++)
            {
                player1.battlefield[x][y+j]=sizeofship*1000+0+i;
            }
           
            player1.ship_coordinates[i][0]=x;
            player1.ship_coordinates[i][1]=y;
            player1.ship_coordinates[i][2]=sizeofship;
            player1.ship_coordinates[i][3]=0;
        }

        else if (form=='v' || form=='V')    //Vertical
        {
            for (int j = 0; j < sizeofship; j++)
            {
                player1.battlefield[x+j][y]=sizeofship*1000+100+i;
            }
            
            player1.ship_coordinates[i][0]=x;
            player1.ship_coordinates[i][1]=y;
            player1.ship_coordinates[i][2]=sizeofship;
            player1.ship_coordinates[i][3]=1;
        }

    }

    fscanf(finput, "%s", temp);

    fgets(temp, 2, finput);
    fgets(player2.name, 100, finput);     
    length = strlen(player2.name);       //deleting '\n'
    player2.name[length-1] = 0;

    //putting ships for player2:
    for (int i = 0; i < nShip; i++)
    {
        fscanf(finput, "%i %i %c", &x, &y, &form);    
        x--; y--;
        if (form=='H' || form=='h')     //Horizental
        {
            for (int j = 0; j < sizeofship; j++)
            {
                player2.battlefield[x][y+j]=sizeofship*1000+0+i;
            }
           
            player2.ship_coordinates[i][0]=x;
            player2.ship_coordinates[i][1]=y;
            player2.ship_coordinates[i][2]=sizeofship;
            player2.ship_coordinates[i][3]=0;
            
        }

        else if (form=='v' || form=='V')    //Vertical
        {
            for (int j = 0; j < sizeofship; j++)
            {
                player2.battlefield[x+j][y]=sizeofship*1000+100+i;
            }
            
            player2.ship_coordinates[i][0]=x;
            player2.ship_coordinates[i][1]=y;
            player2.ship_coordinates[i][2]=sizeofship;
            player2.ship_coordinates[i][3]=1;
        }
    }

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