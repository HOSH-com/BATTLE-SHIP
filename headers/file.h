void file_game_setting();
void file_save_round();


void file_game_setting()
{   
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
    fwrite(&last_round, sizeof(LAST_ROUND), 1, fround);
}


