#include <iostream>

using namespace std;


// Kolory tekstowe
#define B  "\033[30m"      /* Czarny */
#define C  "\033[31m"      /* Czerwony */
#define G  "\033[32m"      /* Zielony */
#define Y  "\033[33m"      /* Żółty */
#define N  "\033[34m"      /* Niebieski */
//#define M  "\033[35m"      /* Magenta */
//#define C  "\033[36m"      /* Cyjan */
#define W  "\033[37m"      /* Biały */
#define R  "\033[0m"       /* Zresetowanie kolorów */


/* 0:╔ 1:╚ 2:╗ 3:╝ 4:║ 5:═ 6:┌ 7:┐ 8:└ 9:┘ 10:│ 11:─ 12:┼ 13:┬ 14:├ 15:┴ 16:┤*/
const char znaki[17] = { (char)201, (char)187, (char)200, (char)188, (char)186, (char)205,
                         (char)218, (char)191, (char)192, (char)217, (char)179, (char)196,
                         (char)197, (char)194, (char)195, (char)193, (char)180};
/* 0:w 1:s 2:a 3:d 4:q 5:u 6:r 7:space 8:o 9:k 10:p 11:h 12:N 13:M*/
const char keyType[14] = { 'W', 'S', 'A', 'D', 'Q', 'U', 'R', ' ', 'O', 'K', 'P', 'H', 'N', 'M'};
const int rozmiarXMax = 110;
const int rozmiarYMax = 55;



void WyswietlPlansze(char key, char**tab, int aktWiel, int rozmiarXAkt,
    int rozmiarYAkt, int ods, int pozycja[2], char**tabColor);

/*
void Cursor(bool jaki)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = jaki;
    SetConsoleCursorInfo(out, &cursorInfo);
}*/




int main() {
    #pragma region zmienne
    //bool keyDown[14]{}; for (int i = 0; i < 14; i++) keyDown[i] = false;
    char **tab = new char*[rozmiarXMax];
    for (int i = 0; i < rozmiarXMax; ++i)
    {
        tab[i] = new char[rozmiarYMax];
    }
    for (int y = 0; y < rozmiarYMax; ++y){
        for (int x = 0; x < rozmiarXMax; ++x){
            tab[x][y] = ' ';
        }
    }

    char** tabColor = new char* [rozmiarXMax];
    for (int i = 0; i < rozmiarXMax; ++i)
    {
        tabColor[i] = new char[rozmiarYMax];
    }
    for (int y = 0; y < rozmiarYMax; ++y) {
        for (int x = 0; x < rozmiarXMax; ++x) {
            tabColor[x][y] = 'R';
        }
    }


    int aktWiel = 10;
    int rozmiarXAkt = rozmiarXMax-1;
    int rozmiarYAkt = rozmiarYMax-1;

    int ods = (rozmiarYAkt + 1) / (aktWiel+1);

    rozmiarYAkt = ods * aktWiel;
    rozmiarXAkt = rozmiarYAkt * 2;

    int pozycja[2]{ 0,0};
    int lokalizacja[16]{};
    for (int i = 0; i < 16; i++)
    {
        lokalizacja[i] = -5;
    }
    char key = '-';
    #pragma endregion

    cout << "\x1B[2J\x1B[H";
    //Cursor(false);
    WyswietlPlansze(NULL, tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods, pozycja, tabColor);
    while (true)
    {
        key = cin.get();
        if ((int)key > 91)
        {
            key = (char)((int)key - 32);
        }
        for (int i = 0; i < 14; i++)
        {
            if (key == keyType[i])
            {
                switch (keyType[i])
                {
                    case 'N': // więcej
                        if (aktWiel != 12) { aktWiel++; }break;
                    case 'M': // mniej
                        if ((aktWiel != 7) && (pozycja[1] < aktWiel - 1) && (pozycja[0] < aktWiel - 1)){ aktWiel--; }break;
                    case 'W':
                        if (pozycja[0] != 0) { pozycja[0]--; } break;
                    case 'S':
                        if (pozycja[0] < aktWiel - 1) { pozycja[0]++; } break;
                    case 'A':
                        if (pozycja[1] != 0) { pozycja[1]--; } break;
                    case 'D':
                        if (pozycja[1] < aktWiel - 1) { pozycja[1]++; } break;

                    default:
                        break;
                }



                for (int y = 0; y < rozmiarYMax; y++) {
                    for (int x = 0; x < rozmiarXMax; x++) {
                        tab[x][y] = ' ';
                    }
                }
                for (int y = 0; y < rozmiarYMax; ++y) {
                    for (int x = 0; x < rozmiarXMax; ++x) {
                        tabColor[x][y] = (short)0;
                    }
                }
                rozmiarXAkt = rozmiarXMax - 1;
                rozmiarYAkt = rozmiarYMax - 1;
                ods = (rozmiarYAkt + 1) / (aktWiel + 1);
                rozmiarYAkt = ods * aktWiel;
                rozmiarXAkt = rozmiarYAkt * 2;
                WyswietlPlansze(keyType[i], tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods, pozycja, tabColor);
            }

        }
    }

    for (int i = 0; i < rozmiarXMax; ++i) {
        delete[] tab[i];
        delete[] tabColor[i];
    }
    delete[] tab;
    delete[] tabColor;

    return 0;
}

void WyswietlPlansze(char key, char**tab, int aktWiel,  int rozmiarXAkt,
    int rozmiarYAkt, int ods, int pozycja[2], char**tabColor)
{
    #pragma region pusta plansza
    int pozX = 0;
    int pozY = 0;

    for (int y = 0; y < aktWiel; y++)
    {
        for (int x = 0; x < aktWiel; x++)
        {
            pozX = x*ods*2;
            pozY = y*ods;

            for (int iy = 0; iy <= ods; iy++)
            {
                pozX = x * ods * 2;
                tab[pozX][pozY] = znaki[10];
                tab[pozX + ods*2][pozY] = znaki[10];
                for (int ix = 0; ix <= ods*2; ix++)
                {
                    if (iy == 0)
                    {
                        tab[pozX][pozY] = znaki[11];
                    }
                    else if (iy == ods-1)
                    {
                        tab[pozX][pozY+1] = znaki[11];
                    }
                    pozX++;
                }
                pozY++;
            }
        }
    }

    for (int y = 0; y <= aktWiel*ods; y++)
    {
        for (int x = 0; x <= aktWiel * ods*2; x++)
        {
            if (y > 0 && y %ods == 0 && tab[x][y] != ' ' && tab[x][y - 1] != ' ') {
                tab[x][y] = znaki[15];
                if (y < rozmiarYAkt && tab[x][y + 1] != ' ') {
                    tab[x][y] = znaki[12];
                }
            }
            else if (y == 0 && tab[x][y+1] != ' ')
            {
                tab[x][y] = znaki[13];
            }
        }
        if (tab[0][y] == znaki[12]) {
            tab[0][y] = znaki[14];
        }
        if (tab[aktWiel*ods*2][y] == znaki[12]) {
            tab[aktWiel*ods*2][y] = znaki[16];
        }
    }

    tab[0][0] = znaki[6];
    tab[rozmiarXAkt][0] = znaki[7];
    tab[0][rozmiarYAkt] = znaki[8];
    tab[rozmiarXAkt][rozmiarYAkt] = znaki[9];


    #pragma endregion

    for (int y = 0; y < rozmiarYAkt; y++)
    {
        for (int x = 0; x < rozmiarXAkt; x++)
        {
            if (tab[x][y] == ' ')
            {
                tab[x][y] = (char)219;
                tabColor[x][y] = 'C';
            }
            if (y >= ods && y < rozmiarYAkt - ods && x >= ods*2 && x < rozmiarXAkt - ods*2)
            {
                x = rozmiarXAkt - ods*2;
            }
        }
    }



    for (int y = pozycja[0]*ods+2; y < pozycja[0] * ods+ods-1; y++)
    {
        for (int x = pozycja[1] * ods*2+3; x < pozycja[1] * 2*ods + 2*ods-2; x++)
        {
            tab[x][y] = (char)219;
            tabColor[x][y] = 'Y';
        }
    }
    cout << "\x1B[2J\x1B[H"; //system("cls");
    for (int y = 0; y <= rozmiarYAkt; y++)
    {
        for (int x = 0; x <= rozmiarXAkt; x++)
        {
            //SetConsoleTextAttribute(hConsole, tabColor[x][y]);
            switch (tabColor[x][y])
            {
                case 'R':
                    cout << R << tab[x][y]; break;
                case 'C':
                    cout << C << tab[x][y]; break;
                case 'Y':
                    cout << Y << tab[x][y]; break;
                default:
                    cout << R << tab[x][y];break;
            }
        }
        if(y!= rozmiarYAkt)cout << "\n";
    }
    //cout << pozycja[0] << " " << pozycja[1];

}