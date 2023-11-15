#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <math.h>

using namespace std;

/* 0:╔ 1:╚ 2:╗ 3:╝ 4:║ 5:═ 6:┌ 7:┐ 8:└ 9:┘ 10:│ 11:─ 12:┼ 13:┬ 14:├ 15:┴ 16:┤*/
const char znaki[17] = { (char)201, (char)187, (char)200, (char)188, (char)186, (char)205,
                         (char)218, (char)191, (char)192, (char)217, (char)179, (char)196,
                         (char)197, (char)194, (char)195, (char)193, (char)180};
/* 0:w 1:s 2:a 3:d 4:q 5:u 6:r 7:space 8:o 9:k 10:p 11:h */
const char keyType[12] = { 'W', 'S', 'A', 'D', 'Q', 'U', 'R', ' ', 'O', 'K', 'P', 'H' };
const int rozmiarXMax = 110;
const int rozmiarYMax = 55;



void rob(char key, char tab[rozmiarXMax][rozmiarYMax], int aktWiel, int rozmiarXAkt, int rozmiarYAkt, int ods);

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
    bool keyDown[12]{}; for (int i = 0; i < 12; i++) keyDown[i] = false;
    char tab[rozmiarXMax][rozmiarYMax]{};
    for (int y = 0; y < rozmiarYMax; y++){
        for (int x = 0; x < rozmiarXMax; x++){
            tab[x][y] = ' ';
        }
    }
    int aktWiel = 10;
    int rozmiarXAkt = rozmiarXMax-1;
    int rozmiarYAkt = rozmiarYMax-1;
    int ods = (rozmiarYAkt + 1) / (aktWiel+1);

    rozmiarYAkt = 4 + ods * aktWiel;
    rozmiarXAkt = rozmiarYAkt * 2;

#pragma endregion

    cout << "\x1B[2J\x1B[H" << endl;
    ShowConsoleCursor(false);
    rob(NULL, tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods);
    while (true)
    {
        for (int i = 0; i < 12; i++)
        {
            if ((GetAsyncKeyState(keyType[i]) & 0x8000) && (keyDown[i] == false))
            {
                keyDown[i] = true;
                //cout << keyType[i] << " ";
                if (keyType[i] == 'A' && aktWiel != 12)
                {
                    aktWiel++;
                }
                if (keyType[i] == 'D' && aktWiel != 1)
                {
                    aktWiel--;
                }
                for (int y = 0; y < rozmiarYMax; y++) {
                    for (int x = 0; x < rozmiarXMax; x++) {
                        tab[x][y] = ' ';
                    }
                }
                rozmiarXAkt = rozmiarXMax - 1;
                rozmiarYAkt = rozmiarYMax - 1;
                ods = (rozmiarYAkt + 1) / (aktWiel + 1);
                rozmiarYAkt = 4 + ods * aktWiel;
                rozmiarXAkt = rozmiarYAkt * 2;
                rob(keyType[i], tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods);
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

void rob(char key, char tab[rozmiarXMax][rozmiarYMax], int aktWiel,  int rozmiarXAkt,  int rozmiarYAkt, int ods)
{
    


    for (int y = 0; y <= rozmiarYAkt; y++)
    {
        tab[0][y] = znaki[4];
        tab[rozmiarXAkt][y] = znaki[4];
        if (y >= 2 && y <= rozmiarYAkt - 2)
        {
            for (int i = 0; i < rozmiarXAkt-4; i+=ods*2)
            {
                tab[4+i][y] = znaki[10];
            }
        }
        for (int x = 0; x <= rozmiarXAkt; x++)
        {
            if (y == 0 || y == rozmiarYAkt)
            {
                tab[x][y] = znaki[5];
            }
        }
    }
    for (int x = 4; x < rozmiarXAkt-3; x++)
    {
        for (int y = 2; y <= rozmiarYAkt-2; y+=ods)
        {
            if (tab[x][y] == znaki[10]) 
            {
                if (x == 4)
                {
                    tab[x][y] = znaki[14];
                }
                else if (x == rozmiarXAkt-4)
                {
                    tab[x][y] = znaki[16];
                }
                else if (y == 2) 
                {
                    tab[x][y] = znaki[13];
                }
                else if (y == rozmiarYAkt-2)
                {
                    tab[x][y] = znaki[15];
                }
                else
                {
                    tab[x][y] = znaki[12];
                }
            }
            else
            {
                tab[x][y] = znaki[11];
            }
        }
    }




    tab[0][0] = znaki[0];
    tab[rozmiarXAkt][0] = znaki[1];
    tab[0][abs(rozmiarYAkt)] = znaki[2];
    tab[abs(rozmiarXAkt)][abs(rozmiarYAkt)] = znaki[3];

    tab[4][2] = znaki[6];
    tab[rozmiarXAkt-4][2] = znaki[7];
    tab[4][abs(rozmiarYAkt-2)] = znaki[8];
    tab[abs(rozmiarXAkt-4)][abs(rozmiarYAkt-2)] = znaki[9];




    cout << "\x1B[2J\x1B[H";
    for (int y = 0; y <= rozmiarYAkt; y++)
    {
        for (int x = 0; x <= rozmiarXAkt; x++)
        {
            cout << tab[x][y];
        }
        cout << "\n";
    }
}