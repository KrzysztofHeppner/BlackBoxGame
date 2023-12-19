#include <iostream>

using namespace std;

#define B  "\033[30m"      /* Czarny */
#define C  "\033[31m"      /* Czerwony */
#define G  "\033[32m"      /* Zielony */
#define Y  "\033[33m"      /* Żółty */
#define N  "\033[34m"      /* Niebieski */
#define W  "\033[37m"      /* Biały */
#define R  "\033[0m"       /* Zresetowanie kolorów */


/* 0:╔ 1:╚ 2:╗ 3:╝ 4:║ 5:═ 6:┌ 7:┐ 8:└ 9:┘ 10:│ 11:─ 12:┼ 13:┬ 14:├ 15:┴ 16:┤*/
const char znaki[17] = { (char)201, (char)187, (char)200, (char)188, (char)186, (char)205,
                         (char)218, (char)191, (char)192, (char)217, (char)179, (char)196,
                         (char)197, (char)194, (char)195, (char)193, (char)180};
/* 0:w 1:s 2:a 3:d 4:q 5:u 6:r 7:space 8:o 9:k 10:p 11:h 12:N 13:M*/
const char keyType[15] = { 'W', 'S', 'A', 'D', 'Q', 'U', 'R', ' ', 'O', 'K', 'P', 'H', 'N', 'M', 'L'};
const int rozmiarXMax = 110;
const int rozmiarYMax = 55;

void WyswietlPlansze(char key, char**tab, int aktWiel, int rozmiarXAkt, int rozmiarYAkt, int ods, 
    int pozycja[2], char**tabColor, bool czyPokazac, int ileAtomow, int lokalizacja[16], char** tabNapisy, int zaznaczone[16], int zaznaczonych);

void Losuj(int lokalizacja[16], int ileAtomow, int aktWiel);

void Start(int* aktWiel, int* ileAtomow);

void Strzal(int* aktWiel, int* ileAtomow, int lokalizacja[16], char **tabNapisy, char kierunek, int* pozycja, int ods, int *kolejnyNumer);

int main() {
    #pragma region zmienne
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

    char** tabNapisy = new char* [rozmiarXMax];
    for (int i = 0; i < rozmiarXMax; ++i)
    {
        tabNapisy[i] = new char[rozmiarYMax];
    }
    for (int y = 0; y < rozmiarYMax; ++y) {
        for (int x = 0; x < rozmiarXMax; ++x) {
            tabNapisy[x][y] = ' ';
        }
    }

    int aktWiel = 10, ileAtomow = 5;
    int rozmiarXAkt = rozmiarXMax-1;
    int rozmiarYAkt = rozmiarYMax-1;

    int ods = (rozmiarYAkt + 1) / (aktWiel+1);

    rozmiarYAkt = ods * aktWiel;
    rozmiarXAkt = rozmiarYAkt * 2;
    // górny lewy y x
    int pozycja[2]{ 0,0};
    int lokalizacja[16]{};
    for (int i = 0; i < 16; i++)
    {
        lokalizacja[i] = -5;
    }
    int zaznaczonych = 0;
    int zaznaczone[16]{};
    for (int i = 0; i < 16; i++)
    {
        zaznaczone[i] = -4;
    }
    char key = '-';
    char kierunek = '-';
    bool czyPokazac = false;

    int wynik = 0;
    int kolejnyNumer = 0;

    char ostatnie[50];
    for (int i = 0; i < 10; i++)
    {
        ostatnie[i] = '|';
    }
    int ileOstatnich = 0;
    int ostatnieLok[100];
    for (int i = 0; i < 50; i++)
    {
        ostatnieLok[i*2] = '-9';
        ostatnieLok[i*2+1] = '-9';
    }


    srand((unsigned int)time(NULL));
    #pragma endregion

    system("cls");
    Start(&aktWiel, &ileAtomow);

    Losuj(lokalizacja, ileAtomow, aktWiel);

    rozmiarXAkt = rozmiarXMax - 1;
    rozmiarYAkt = rozmiarYMax - 1;

    ods = (rozmiarYAkt + 1) / (aktWiel + 1);

    rozmiarYAkt = ods * aktWiel;
    rozmiarXAkt = rozmiarYAkt * 2;

    WyswietlPlansze(NULL, tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods, pozycja, tabColor, czyPokazac, ileAtomow, lokalizacja, tabNapisy, zaznaczone, zaznaczonych);

    while (true)
    {
        key = cin.get();
        if ((int)key > 91){
            key = (char)((int)key - 32);
        }
        for (int i = 0; i < 15; i++)
        {
            if (key == keyType[i])
            {
                switch (keyType[i])
                {
                    case 'N': // więcej
                        if (aktWiel != 24) { 
                            aktWiel++;
                            if (aktWiel == 7) ileAtomow = 3;
                            if (aktWiel == 10) ileAtomow = 5;
                            if (aktWiel == 12) ileAtomow = 8;
                            Losuj(lokalizacja, ileAtomow, aktWiel);
                            for (int y = 0; y < rozmiarYMax; ++y) {
                                for (int x = 0; x < rozmiarXMax; ++x) {
                                    tabNapisy[x][y] = ' ';
                                }
                            }
                            kolejnyNumer = 0;
                            zaznaczonych = 0;
                            ileOstatnich = 0;
                        }break;
                    case 'M': // mniej
                        if ((aktWiel != 7) && (pozycja[1] < aktWiel - 1) && (pozycja[0] < aktWiel - 1)){ 
                            aktWiel--;
                            if (aktWiel == 7) ileAtomow = 3;
                            if (aktWiel == 10) ileAtomow = 5;
                            if (aktWiel == 12) ileAtomow = 8;
                            Losuj(lokalizacja, ileAtomow, aktWiel);
                            for (int y = 0; y < rozmiarYMax; ++y) {
                                for (int x = 0; x < rozmiarXMax; ++x) {
                                    tabNapisy[x][y] = ' ';
                                }
                            }
                            kolejnyNumer = 0;
                            zaznaczonych = 0;
                            ileOstatnich = 0;
                        }break;
                    case 'W':
                        if (pozycja[0] != 0) { pozycja[0]--; } break;
                    case 'S':
                        if (pozycja[0] < aktWiel - 1) { pozycja[0]++; } break;
                    case 'A':
                        if (pozycja[1] != 0) { pozycja[1]--; } break;
                    case 'D':
                        if (pozycja[1] < aktWiel - 1) { pozycja[1]++; } break;
                    case 'Q':
                        cin.get();
                        Start(&aktWiel, &ileAtomow); 
                        Losuj(lokalizacja, ileAtomow, aktWiel); 
                        for (int y = 0; y < rozmiarYMax; ++y) {
                            for (int x = 0; x < rozmiarXMax; ++x) {
                                tabNapisy[x][y] = ' ';
                            }
                        }
                        kolejnyNumer = 0;
                        zaznaczonych = 0;
                        ileOstatnich = 0; break;
                    case 'H':
                        czyPokazac = true; break;
                    case 'P':
                        czyPokazac = true; break;
                    case 'L':
                        Losuj(lokalizacja, ileAtomow, aktWiel); 
                        for (int y = 0; y < rozmiarYMax; ++y) {
                            for (int x = 0; x < rozmiarXMax; ++x) {
                                tabNapisy[x][y] = ' ';
                            }
                        }
                        kolejnyNumer = 0;
                        break;
                    case 'K':
                        for (int kk = 0; kk < zaznaczonych; kk++)
                        {
                            tabNapisy[zaznaczone[kk*2] * ods * 2 + ods][zaznaczone[kk * 2+1] * ods + ods / 2] = 'X';
                        }
                        for (int ii = 0; ii < zaznaczonych; ii++)
                        {
                            for (int jj = 0; jj < ileAtomow; jj++)
                            {
                                if (zaznaczone[ii*2]==lokalizacja[jj*2] && zaznaczone[ii * 2+1] == lokalizacja[jj * 2+1])
                                {
                                    tabNapisy[zaznaczone[ii * 2] * ods * 2 + ods][zaznaczone[ii * 2+1] * ods + ods / 2] = 'O';
                                    wynik++;
                                }
                            }
                        }
                        czyPokazac = true;
                        goto pomin; break;
                    case 'O':
                        if (zaznaczonych<ileAtomow)
                        {
                            for (int j = zaznaczonych; j < 50; j++)
                            {
                                ostatnie[j] = '|';
                            }
                            for (int k = 0; k < zaznaczonych; k++)
                            {
                                if ((zaznaczone[k * 2] == pozycja[1]) && (zaznaczone[k * 2 + 1] == pozycja[0]))
                                {
                                    goto pomin;
                                }
                            }

                            zaznaczone[zaznaczonych * 2] = pozycja[1];
                            zaznaczone[zaznaczonych * 2 + 1] = pozycja[0];
                            zaznaczonych++;

                            ostatnie[ileOstatnich] = 'O';
                            ostatnieLok[ileOstatnich * 2] = pozycja[1];
                            ostatnieLok[ileOstatnich * 2 + 1] = pozycja[0];
                            ileOstatnich++;
                        }
                        break;
                    case 'U':
                        if (ileOstatnich > 0)
                        {
                            if (ostatnie[ileOstatnich - 1] == 'O')
                            {
                                if (zaznaczonych > 0)
                                {
                                    zaznaczonych--;
                                }
                            }
                            ileOstatnich--;
                        }break;
                    case 'R':
                        if (ileOstatnich <= zaznaczonych)
                        {
                            if (ostatnie[ileOstatnich] == 'O')
                            {
                                zaznaczonych++;
                                ileOstatnich++;
                            }
                        }break;
                    case ' ':
                        if ((pozycja[0] == 0) && !((pozycja[1] == 0) || (pozycja[1] == aktWiel-1))) {
                            kierunek = 'd';
                            Strzal(&aktWiel, &ileAtomow, lokalizacja, tabNapisy, kierunek, pozycja, ods, &kolejnyNumer);
                        }
                        else if ((pozycja[0] == aktWiel - 1) && !((pozycja[1] == 0) || (pozycja[1] == aktWiel - 1))) {
                            kierunek = 'g';
                            Strzal(&aktWiel, &ileAtomow, lokalizacja, tabNapisy, kierunek, pozycja, ods, &kolejnyNumer);
                        }
                        else if ((pozycja[1] == 0) && !((pozycja[0] == 0) || (pozycja[0] == aktWiel - 1))) {
                            kierunek = 'p';
                            Strzal(&aktWiel, &ileAtomow, lokalizacja, tabNapisy, kierunek, pozycja, ods, &kolejnyNumer);
                        }
                        else if ((pozycja[1] == aktWiel - 1) && !((pozycja[0] == 0) || (pozycja[0] == aktWiel - 1))) {
                            kierunek = 'l';
                            Strzal(&aktWiel, &ileAtomow, lokalizacja, tabNapisy, kierunek, pozycja, ods, &kolejnyNumer);
                        }break;
                    default:
                        break;
                }
                pomin:
                if (key == 'H') 
                {
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
                    WyswietlPlansze(keyType[i], tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods, pozycja, tabColor, czyPokazac, ileAtomow, lokalizacja, tabNapisy, zaznaczone, zaznaczonych);

                    clock_t star = clock();
                    while ((clock() - star) / CLOCKS_PER_SEC < 1) {}
                    czyPokazac = false;
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
                WyswietlPlansze(keyType[i], tab, aktWiel, rozmiarXAkt, rozmiarYAkt, ods, pozycja, tabColor, czyPokazac, ileAtomow, lokalizacja, tabNapisy, zaznaczone, zaznaczonych);
                if (key == 'P' || key == 'K')
                {
                    goto koniec;
                }
            }

        }
    }
    koniec:
    if (key == 'K')
    {
        cout << "Zdobyte punkty: " << wynik;
    }

    for (int i = 0; i < rozmiarXMax; ++i) {
        delete[] tab[i];
        delete[] tabColor[i];
        delete[] tabNapisy[i];
    }
    delete[] tab;
    delete[] tabColor;
    delete[] tabNapisy;

    return 0;
}

void Losuj(int lokalizacja[16], int ileAtomow, int aktWiel)
{
    bool czyDobry = true;
    int tempX = -5, tempY = -5;
    tempX = -5, tempY = -5;
    for (int k = 0; k < 16; k++)
    {
        lokalizacja[k] = -2;
    }
    for (int i = 0; i < ileAtomow; i++)
    {
        czyDobry = true;
        while (czyDobry)
        {
            czyDobry = false;
            tempX = rand() % (aktWiel - 2) + 1;
            tempY = rand() % (aktWiel - 2) + 1;
            for (int j = 0; j < aktWiel; j++)
            {
                if (tempX == lokalizacja[j * 2] && tempY == lokalizacja[j * 2 + 1]) {
                    czyDobry = true;
                }
            }
        }
        lokalizacja[i * 2] = tempX;
        lokalizacja[i * 2 + 1] = tempY;
    }
}


void Start(int* aktWiel, int* ileAtomow)
{
    system("cls");
    char znak = '|';
    cout << "************************************************************\n";
    cout << "*                                                          *\n";
    cout << "*                                                          *\n";
    cout << "*                Witam w the Black Box Game                *\n";
    cout << "*                                                          *\n";
    cout << "*                                                          *\n";
    cout << "************************************************************\n";
    cout << "\nOpcje startowe gry (mo" << (char)190 << "na zmienic p" << (char)162 << (char)171 << "niej): \n";
    cout << "1) rozmiar 5x5 z 3 atomami\n";
    cout << "2) rozmiar 8x8 z 5 atomami\n";
    cout << "3) rozmiar 10x10 z 8 atomami\n";
    cout << "Tw" << (char)162 << "j wybor: ";
    
    znak = cin.get();

    switch (znak)
    {
    case '1':
        *aktWiel = 5+2;
        *ileAtomow = 3;
        break;
    case '2':
        *aktWiel = 8+2;
        *ileAtomow = 5;
        break;
    case '3':
        *aktWiel = 10+2;
        *ileAtomow = 8;
        break;
    default:
        cout << "z" << (char)136 << "a liczba - ustawiono 1 opcje - wcisnij dowolny klawisz aby kontynuowa" << (char)134;
        cin.get();
        cin.get();
        *aktWiel = 5+2;
        *ileAtomow = 3;
        break;
    }
    
}


void WyswietlPlansze(char key, char**tab, int aktWiel,  int rozmiarXAkt, int rozmiarYAkt, int ods, 
    int pozycja[2], char**tabColor, bool czyPokazac, int ileAtomow, int lokalizacja[16], char** tabNapisy, int zaznaczone[16], int zaznaczonych)
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
    //obramówka
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


    //zaznaczone
    for (int i = 0; i < zaznaczonych; i++)
    {
        for (int y = zaznaczone[i * 2 + 1] * ods + 1; y < zaznaczone[i * 2 + 1] * ods + ods; y++)
        {
            for (int x = zaznaczone[i * 2] * ods * 2 + 1; (x < zaznaczone[i * 2] * 2 * ods + 2 * ods) && x < rozmiarXMax; x++)
            {
                tab[x][y] = (char)219;
                tabColor[x][y] = 'N';
            }
        }
    }
    //atomy
    if (czyPokazac)
    {
        for (int i = 0; i < ileAtomow; i++)
        {
            for (int y = lokalizacja[i*2+1] * ods + 1; y < lokalizacja[i * 2 + 1] * ods + ods; y++)
            {
                for (int x = lokalizacja[i*2] * ods * 2 + 1; (x < lokalizacja[i*2] * 2 * ods + 2 * ods) && x < rozmiarXMax; x++)
                {
                    tab[x][y] = (char)219;
                    tabColor[x][y] = 'G';
                }
            }
        }
    }

    //kursor
    if (ods - 3 > 0)
    {
        for (int y = pozycja[0] * ods + 2; y < pozycja[0] * ods + ods - 1; y++)
        {
            for (int x = pozycja[1] * ods * 2 + 3; x < pozycja[1] * 2 * ods + 2 * ods - 2; x++)
            {
                tab[x][y] = (char)219;
                tabColor[x][y] = 'Y';
            }
        }
    }
    else
    {
        for (int y = pozycja[0] * ods + 1; y < pozycja[0] * ods + ods ; y++)
        {
            for (int x = pozycja[1] * ods * 2 + 1; x < pozycja[1] * 2 * ods + 2 * ods ; x++)
            {
                tab[x][y] = (char)219;
                tabColor[x][y] = 'Y';
            }
        }
    }

    //napisy
    for (int y = 0; y < rozmiarYMax; y++)
    {
        for (int x = 0; x < rozmiarXMax; x++)
        {
            if (tabNapisy[x][y] != ' ')
            {
                tab[x][y] = tabNapisy[x][y];
                tabColor[x][y] = 'W';
            }
        }
    }

    system("cls");
    for (int y = 0; y <= rozmiarYAkt; y++)
    {
        for (int x = 0; x <= rozmiarXAkt; x++)
        {
            switch (tabColor[x][y])
            {
                case 'R':
                    cout << R << tab[x][y]; break;
                case 'C':
                    cout << C << tab[x][y]; break;
                case 'Y':
                    cout << Y << tab[x][y]; break;
                case 'G':
                    cout << G << tab[x][y]; break;
                case 'B':
                    cout << B << tab[x][y]; break;
                case 'N':
                    cout << N << tab[x][y]; break;
                default:
                    cout << R << tab[x][y]; break;
            }
        }
        switch (y)
        {
        case 2:
            cout << "     Atom" << (char)162 << "w: " << ileAtomow; break;
        case 3:
            cout << "     ************ Menu ************"; break;
        case 5:
            cout << "     *  ruch kursora: w,s,a,d     *"; break;
        case 6:
            cout << "     *  wyj" << (char)152 << (char)134 << "ie do menu: q        *"; break;
        case 7:
            cout << "     *  undo: u                   *"; break;
        case 8:
            cout << "     *  redo: r                   *"; break;
        case 9:
            cout << "     *  strza" << (char)136 << ": spacja            *"; break;
        case 10:
            cout << "     *  zaznacz atom: o           *"; break;
        case 11:
            cout << "     *  koniec rozgrywki: k       *"; break;
        case 12:
            cout << "     *  poddaj si" << (char)169 << ": p             *"; break;
        case 13:
            cout << "     *  pomoc (wy" << (char)152 << "wietl atomy): h *"; break;
        case 14:
            cout << "     *  losowanie atom" << (char)162 << "w: l       *"; break;
        case 15:
            cout << "     *  powi" << (char)169 << "kszenie planszy: n   *"; break;
        case 16:
            cout << "     *  pomniejszenie planszy: m  *"; break;
        case 18:
            cout << "     ************ Menu ************"; break;
        default:
            break;
        }

        cout << "\n";
    }
    if (key != 'K')
    {
        cout << "Podaj komendy: ";
    }

}


void Strzal(int* aktWiel, int* ileAtomow, int lokalizacja[16], char** tabNapisy, char kierunek, int* pozycja, int ods, int* kolejnyNumer)
{
    int x = pozycja[1];
    int y = pozycja[0];
    bool czy1 = false, czy2 = false, czy3 = false;
    while (true)
    {
        switch (kierunek)
        {
        case 'p':
            czy1 = false; czy2 = false; czy3 = false;
            for (int i = 0; i < *aktWiel+1; i++)
            {
                if (x + 1 == lokalizacja[i * 2] && y + 1 == lokalizacja[i * 2 + 1])
                {
                    czy1 = true;
                }
                if (x + 1 == lokalizacja[i * 2] && y == lokalizacja[i * 2 + 1])
                {
                    czy2 = true;
                }
                if (x + 1 == lokalizacja[i * 2] && y - 1 == lokalizacja[i * 2 + 1])
                {
                    czy3 = true;
                }
            }
            if (czy2)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'H';
                goto przerwij;
            }
            else if ((czy1 && czy3) && !czy2)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'R';
                goto przerwij;
            }
            else if (czy1 && !czy3)
            {
                kierunek = 'g'; break;
            }
            else if (!czy1 && czy3)
            {
                kierunek = 'd'; break;
            }
            if (x >= *aktWiel-1) 
            {
                if (*kolejnyNumer > 9)
                {
                    tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = (48 + (*kolejnyNumer / 10));
                    tabNapisy[pozycja[1] * ods * 2 + ods + 1][pozycja[0] * ods + ods / 2] = (48 + (*kolejnyNumer % 10));

                    tabNapisy[x * ods * 2 + ods][y * ods + ods / 2] = (48 + (*kolejnyNumer / 10));
                    tabNapisy[x * ods * 2 + ods + 1][y * ods + ods / 2] = (48 + (*kolejnyNumer % 10));
                    *kolejnyNumer += 1;
                }
                else 
                {
                    tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = (48 + *kolejnyNumer);
                    tabNapisy[x * ods * 2 + ods][y * ods + ods / 2] = (48 + *kolejnyNumer);
                    *kolejnyNumer += 1;
                }
                goto przerwij;
            }
            if (y == 0 || y == *aktWiel - 1)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'R';
                goto przerwij;
            }
            x++;
            break;

        case 'l':
            czy1 = false; czy2 = false; czy3 = false;
            for (int i = 0; i < *aktWiel + 1; i++)
            {
                if (x - 1 == lokalizacja[i * 2] && y + 1 == lokalizacja[i * 2 + 1])
                {
                    czy1 = true;
                }
                if (x - 1 == lokalizacja[i * 2] && y == lokalizacja[i * 2 + 1])
                {
                    czy2 = true;
                }
                if (x - 1 == lokalizacja[i * 2] && y - 1 == lokalizacja[i * 2 + 1])
                {
                    czy3 = true;
                }
            }
            if (czy2)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'H';
                goto przerwij;
            }
            else if ((czy1 && czy3) && !czy2)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'R';
                goto przerwij;
            }
            else if (czy1 && !czy3)
            {
                kierunek = 'g'; break;
            }
            else if (!czy1 && czy3)
            {
                kierunek = 'd'; break;
            }
            if (x == 0)
            {
                if (*kolejnyNumer > 9)
                {
                    tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = (48 + (*kolejnyNumer / 10));
                    tabNapisy[pozycja[1] * ods * 2 + ods + 1][pozycja[0] * ods + ods / 2] = (48 + (*kolejnyNumer % 10));

                    tabNapisy[x * ods * 2 + ods][y * ods + ods / 2] = (48 + (*kolejnyNumer / 10));
                    tabNapisy[x * ods * 2 + ods + 1][y * ods + ods / 2] = (48 + (*kolejnyNumer % 10));
                    *kolejnyNumer += 1;
                }
                else
                {
                    tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = (48 + *kolejnyNumer);
                    tabNapisy[x * ods * 2 + ods][y * ods + ods / 2] = (48 + *kolejnyNumer);
                    *kolejnyNumer += 1;
                }
                goto przerwij;
            }
            if (y == 0 || y == *aktWiel - 1)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'R';
                goto przerwij;
            }
            x--;
            break;

        case 'd':
            czy1 = false; czy2 = false; czy3 = false;
            for (int i = 0; i < *aktWiel + 1; i++)
            {
                if (x + 1 == lokalizacja[i * 2] && y + 1 == lokalizacja[i * 2 + 1])
                {
                    czy1 = true;
                }
                if (x == lokalizacja[i * 2] && y + 1 == lokalizacja[i * 2 + 1])
                {
                    czy2 = true;
                }
                if (x - 1 == lokalizacja[i * 2] && y + 1 == lokalizacja[i * 2 + 1])
                {
                    czy3 = true;
                }
            }
            if (czy2)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'H';
                goto przerwij;
            }
            else if ((czy1 && czy3) && !czy2)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'R';
                goto przerwij;
            }
            else if (czy1 && !czy3)
            {
                kierunek = 'l'; break;
            }
            else if (!czy1 && czy3)
            {
                kierunek = 'p'; break;
            }
            if (y >= *aktWiel-1)
            {
                if (*kolejnyNumer > 9)
                {
                    tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = (48 + (*kolejnyNumer / 10));
                    tabNapisy[pozycja[1] * ods * 2 + ods + 1][pozycja[0] * ods + ods / 2] = (48 + (*kolejnyNumer % 10));

                    tabNapisy[x * ods * 2 + ods][y * ods + ods / 2] = (48 + (*kolejnyNumer / 10));
                    tabNapisy[x * ods * 2 + ods + 1][y * ods + ods / 2] = (48 + (*kolejnyNumer % 10));
                    *kolejnyNumer += 1;
                }
                else
                {
                    tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = (48 + *kolejnyNumer);
                    tabNapisy[x * ods * 2 + ods][y * ods + ods / 2] = (48 + *kolejnyNumer);
                    *kolejnyNumer += 1;
                }
                goto przerwij;
            }
            if (x == 0 || x == *aktWiel - 1)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'R';
                goto przerwij;
            }
            y++;
            break;

        case 'g':
            czy1 = false; czy2 = false; czy3 = false;
            for (int i = 0; i < *aktWiel + 1; i++)
            {
                if (x + 1 == lokalizacja[i * 2] && y - 1 == lokalizacja[i * 2 + 1])
                {
                    czy1 = true;
                }
                if (x == lokalizacja[i * 2] && y - 1 == lokalizacja[i * 2 + 1])
                {
                    czy2 = true;
                }
                if (x - 1 == lokalizacja[i * 2] && y - 1 == lokalizacja[i * 2 + 1])
                {
                    czy3 = true;
                }
            }
            if (czy2)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'H';
                goto przerwij;
            }
            else if ((czy1 && czy3) && !czy2)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'R';
                goto przerwij;
            }
            else if (czy1 && !czy3)
            {
                kierunek = 'l'; break;
            }
            else if (!czy1 && czy3)
            {
                kierunek = 'p'; break;
            }
            if (y == 0)
            {
                if (*kolejnyNumer > 9)
                {
                    tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = (48 + (*kolejnyNumer / 10));
                    tabNapisy[pozycja[1] * ods * 2 + ods + 1][pozycja[0] * ods + ods / 2] = (48 + (*kolejnyNumer % 10));

                    tabNapisy[x * ods * 2 + ods][y * ods + ods / 2] = (48 + (*kolejnyNumer / 10));
                    tabNapisy[x * ods * 2 + ods + 1][y * ods + ods / 2] = (48 + (*kolejnyNumer % 10));
                    *kolejnyNumer += 1;
                }
                else
                {
                    tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = (48 + *kolejnyNumer);
                    tabNapisy[x * ods * 2 + ods][y * ods + ods / 2] = (48 + *kolejnyNumer);
                    *kolejnyNumer += 1;
                }
                goto przerwij;
            }
            if (x == 0 || x == *aktWiel - 1)
            {
                kierunek = '*';
                tabNapisy[pozycja[1] * ods * 2 + ods][pozycja[0] * ods + ods / 2] = 'R';
                goto przerwij;
            }
            y--;
            break;
            
        default:
            break;
        }
    }
    przerwij:
    cout << "";
}