#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <math.h>

using namespace std;

/* 0:╔ 1:╚ 2:╗ 3:╝ 4:║ 5:═ 6:┌ 7:┐ 8:└ 9:┘ 10:│ 11:─ 12:┼ 13:┬ 14:├ 15:┴ 16:┤*/
const char znaki[17] = { (char)201, (char)187, (char)200, (char)188, (char)186, (char)205,
                         (char)218, (char)191, (char)192, (char)217, (char)179, (char)196,
                         (char)197, (char)194, (char)195, (char)193, (char)180};
/* 0:w 1:s 2:a 3:d 4:q 5:u 6:r 7:space 8:o 9:k 10:p 11:h 12:N 13:M*/
const char keyType[14] = { 'W', 'S', 'A', 'D', 'Q', 'U', 'R', ' ', 'O', 'K', 'P', 'H', 'N', 'M'};
const int rozmiarXMax = 110;
const int rozmiarYMax = 55;



void WyswietlPlansze(char key, char tab[rozmiarXMax][rozmiarYMax], int aktWiel, int rozmiarXAkt, int rozmiarYAkt, int ods, int pozycja[2]);

//do kursora dla wygląd
void ShowConsoleCursor(bool jaki)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = jaki;
    SetConsoleCursorInfo(out, &cursorInfo);
}




int main() {
    #pragma region zmienne
    bool keyDown[14]{}; for (int i = 0; i < 14; i++) keyDown[i] = false;
    char tab[rozmiarXMax][rozmiarYMax]{};
    for (int y = 0; y < rozmiarYMax; y++){
        for (int x = 0; x < rozmiarXMax; x++){
            tab[x][y] = ' ';
        }
    }
    int aktWiel = 7;
    int rozmiarXAkt = rozmiarXMax-1;
    int rozmiarYAkt = rozmiarYMax-1;

    int ods = (rozmiarYAkt + 1) / (aktWiel+1);

    rozmiarYAkt = ods * aktWiel;
    rozmiarXAkt = rozmiarYAkt * 2;

    int pozycja[2]{ 0,0};
    #pragma endregion

    cout << "\x1B[2J\x1B[H";
    ShowConsoleCursor(false);
    WyswietlPlansze(NULL, tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods, pozycja);
    while (true)
    {
        for (int i = 0; i < 14; i++)
        {
            if ((GetAsyncKeyState(keyType[i]) & 0x8000) && (keyDown[i] == false))
            {
                keyDown[i] = true;
                switch (keyType[i])
                {
                    case 'N':
                        if (aktWiel != 12) { aktWiel++; }break;
                    case 'M':
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
                rozmiarXAkt = rozmiarXMax - 1;
                rozmiarYAkt = rozmiarYMax - 1;
                ods = (rozmiarYAkt + 1) / (aktWiel + 1);
                rozmiarYAkt = ods * aktWiel;
                rozmiarXAkt = rozmiarYAkt * 2;
                WyswietlPlansze(keyType[i], tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods, pozycja);
            }
            if (!(GetAsyncKeyState(keyType[i]) & 0x8000) && (keyDown[i] == true))
            {
                keyDown[i] = false;
            }

        }
        Sleep(10);
    }

    return 0;
}

void WyswietlPlansze(char key, char tab[rozmiarXMax][rozmiarYMax], int aktWiel,  int rozmiarXAkt,  int rozmiarYAkt, int ods, int pozycja[2])
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



    for (int y = pozycja[0]*ods+2; y < pozycja[0] * ods+ods-1; y++)
    {
        for (int x = pozycja[1] * ods*2+3; x < pozycja[1] * 2*ods + 2*ods-2; x++)
        {
            tab[x][y] = (char)219;
        }
    }


    cout << "\x1B[2J\x1B[H"; //system("cls");
    for (int y = 0; y <= rozmiarYAkt; y++)
    {
        for (int x = 0; x <= rozmiarXAkt; x++)
        {
            cout << tab[x][y];
        }
        if(y!= rozmiarYAkt)cout << "\n";
    }
    //cout << pozycja[0] << " " << pozycja[1];

}