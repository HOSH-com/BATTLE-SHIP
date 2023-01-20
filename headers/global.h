#define MAX_COOR 20
#define BLACK 0
#define GREY 8
#define WHITE1 7
#define WHITE2 15
#define BLUE 3
#define RED 4
#define ESC 27
int sizeofship=3;

enum Turn
{
    PLAYER1,
    PLAYER2,
}turn;

struct PLAYERS_INFO
{
    char name[21];
    int number_of_ship = 0;
    int remaining_element;
    int remaining_repair;
    int remaining_ship;
    int battlefield[15][15] = {};
    int ship_coordinates[MAX_COOR][5];
}player1,player2;
struct GAME_SETTING
{
    int size_of_area;
    int max_element;
    int max_repair;
    int nRound;
    int theme=0; //*code 0 for white background and 1 for dark background
    int status;
}setting;

struct LAST_ROUND
{
    struct GAME_SETTING setting;
    struct PLAYERS_INFO player1, player2;
};
