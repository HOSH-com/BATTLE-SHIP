//tools:
void clearScreen();
void sleep(unsigned int mseconds);
void setTextColor(int textColor, int backColor);
int tedad_char(const char p1[]);
void clean_battlefields();
void intSwap(int &a, int &b);
void printError();

void clearScreen()
{
    system("cls");
}

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void setTextColor(int textColor, int backColor)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

int tedad_char(const char pName[])
{
    for (int i = 0; i < 21; i++)
    {
        if (pName[i]=='\0')
        {
            return i;   //name SIZE (i)
        }
    }
    return -1;      //name limit exeeded ERROR (-1)
}

void clean_battlefields()
{
    int i, j;
    for ( i = 0; i < 15; i++)
        for ( j = 0; j < 15; j++)
        {
            player1.battlefield[i][j] = 0;
            player2.battlefield[i][j] = 0;
        }
    
}

void intSwap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void printError()
{
    if (theme == 0)
    {
        setTextColor(RED, WHITE2);
        printf("ERROR: ");
        setTextColor(BLACK, WHITE2);
    }
    else if (theme == 1)
    {
        setTextColor(RED, BLACK);
        printf("ERROR: ");
        setTextColor(WHITE2, BLACK);
    }
}    