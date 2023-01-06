void file_game_setting()
{   
    clearScreen();
    int nShip, x, y, result, length;
    char form, temp[11];
    FILE *finput = fopen("C:\\Users\\ASUS\\Desktop\\BATTLE-SHIP\\input.txt", "rt");
    if (!finput)
    {
        printf("ERROR: can't open the file!\n");
        sleep(5000);
        exit (1);
    }
    fscanf(finput, "%i", &setting.size_of_area);
    fscanf(finput, "%i", &player1[0].number_of_ship);
    nShip = player1[0].remaining_ship = player2[0].remaining_ship = player2[0].number_of_ship = player1[0].number_of_ship;

    fgets(temp, 2, finput);
    fgets(player1[0].name, 100, finput);     //ERROR because of '\n'
    length = strlen(player1[0].name);
    player1[0].name[length-1] = 0;

    //putting ships for player1:
    for (int i = 0; i < nShip; i++)
    {
        fscanf(finput, "%i %i %c", &x, &y, &form);    //ERROR trash 
        x--; y--;
        if (form=='H' || form=='h')     //Horizental
        {
            for (int j = 0; j < sizeofship; j++)
            {
                player1[0].battlefield[x][y+j]=sizeofship*1000+0+i;
            }
           
            player1[0].ship_coordinates[i][0]=x;
            player1[0].ship_coordinates[i][1]=y;
            player1[0].ship_coordinates[i][2]=sizeofship;
            player1[0].ship_coordinates[i][3]=0;
            
        }

        else if (form=='v' || form=='V')    //Vertical
        {
            for (int j = 0; j < sizeofship; j++)
            {
                player1[0].battlefield[x+j][y]=sizeofship*1000+100+i;
            }
            
            player1[0].ship_coordinates[i][0]=x;
            player1[0].ship_coordinates[i][1]=y;
            player1[0].ship_coordinates[i][2]=sizeofship;
            player1[0].ship_coordinates[i][3]=1;
        }

    }

    fscanf(finput, "%s", temp);

    fgets(temp, 2, finput);
    fgets(player2[0].name, 100, finput);     //ERROR because of '\n'
    length = strlen(player2[0].name);
    player2[0].name[length-1] = 0;

    //putting ships for player2:
    for (int i = 0; i < nShip; i++)
    {
        fscanf(finput, "%i %i %c", &x, &y, &form);    //ERROR trash 
        x--; y--;
        if (form=='H' || form=='h')     //Horizental
        {
            for (int j = 0; j < sizeofship; j++)
            {
                player2[0].battlefield[x][y+j]=sizeofship*1000+0+i;
            }
           
            player2[0].ship_coordinates[i][0]=x;
            player2[0].ship_coordinates[i][1]=y;
            player2[0].ship_coordinates[i][2]=sizeofship;
            player2[0].ship_coordinates[i][3]=0;
            
        }

        else if (form=='v' || form=='V')    //Vertical
        {
            for (int j = 0; j < sizeofship; j++)
            {
                player2[0].battlefield[x+j][y]=sizeofship*1000+100+i;
            }
            
            player2[0].ship_coordinates[i][0]=x;
            player2[0].ship_coordinates[i][1]=y;
            player2[0].ship_coordinates[i][2]=sizeofship;
            player2[0].ship_coordinates[i][3]=1;
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