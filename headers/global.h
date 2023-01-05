#define MAX_COOR 20

#ifndef global
#define global

int player1_ship_Coordinates[20][4] = {0};
int player2_ship_Coordinates[20][4] = {0};
struct PLAYERS_INFO
{
    char name[21];
    int number_of_ship;
    int remaining_ship;
    int battlefield[15][15];
    int ship_coordinates[MAX_COOR][4];
}player1[100],player2[100];
struct GAME_SETTING
{
    int size_of_area;
    int max_element;
    int max_repair;
    int nRound;
}setting;

#endif