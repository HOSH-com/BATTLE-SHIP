//tools:
void clearScreen();
void sleep(unsigned int mseconds);
void setTextColor(int textColor, int backColor);
int tedad_char(const char p1[]);

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
    for (int i = 0; i < NAME_LIMIT; i++)
    {
        if (pName[i]=='\0')
        {
            return i;   //name SIZE (i)
        }
    }
    return -1;      //name limit exeeded ERROR (-1)
}
