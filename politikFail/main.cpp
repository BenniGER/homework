#include <QCoreApplication>
#include <string>
#include <iostream>
#include <sstream>
//#include <iomanip>
#include <Windows.h>
#include <cstdlib>


using namespace std;
#define stringify( name ) # name
#define ENUM2STR_BEGIN(VAR) switch( VAR ){
#define ENUM2STR(EN) case EN: return std::string( #EN );
#define ENUM2STR_END(ERR) }; return std::string( ERR );

int* personen;
int personenSize;
int parteiSize;
string* parteien;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum Color {
    NONE = 0,
    BLACK, RED, GREEN,
    YELLOW, BLUE, MAGENTA,
    CYAN, WHITE
};

int* parteiColors = new int[9];

int mod(int a, int b){
  return (a%b+b)%b;
}

int getPersonRandomNeigbor(int person) {

    int maxRow = sqrt(personenSize);
    // int row = ceil(((double)person+1) / ((double)maxRow));
    int random = rand() % 4;
    int position;
    switch (random) {
        case 0: {
            position = mod((person - 1 + maxRow) % maxRow, maxRow) + (((int)personenSize / maxRow) * maxRow);
            break;
        }
        case 1: {
            position = mod((person + 1 - maxRow) % maxRow, maxRow) + (((int)personenSize / maxRow) * maxRow);
            break;
        }
        case 2: {
            position = mod(person - maxRow, personenSize);
            break;
        }
        case 3: {
            position = mod(person + maxRow, personenSize);
            break;
        }
        default: {
            cout << "getPersonRandomNeigbor Broken" << endl;
        }
     }
     return position;
}

void initPerson() {
    for (int var = 0; var < personenSize; ++var) {
      personen[var] = rand()% parteiSize;
    }
}

bool check(const int a[], int n) {
    return !std::all_of(a, a+n, [a](int x){ return x==a[0]; });
}


void ui() {

    int maxRow = sqrt(personenSize);

    string test;
    int temp = 2;
    system("cls");

    for (int var = 0; var < personenSize; ++var) {
         int row = ceil(((double)var+1) / ((double)maxRow));
        if (row == temp) {
            ++temp;
             cout  << "\n";
        }
        int color = parteiColors[personen[var]];
        SetConsoleTextAttribute(hConsole,color);
        cout  << "  " <<parteien[personen[var]];
    }
}

int main(int argc, char *argv[])
{

    system("mode 650");
    system("title Politik");

    cout << "Size:";
    cin >> personenSize;
    cout << "Partei Menge:";
    cin >> parteiSize;
    personen = new int[personenSize];
    parteien = new string[parteiSize];
    parteiColors = new int[parteiSize];


    for (int var = 0; var < parteiSize; var++) {
        cout << "Partei Name:";
        cin >> parteien[var];

        cout << "Partei Color Code:";
        cin >> parteiColors[var];
    }

    initPerson();

    ui();
    bool win = false;
    int temp = 0;
    while (!win) {

        for (int var = 0; var < parteiSize; ++var) {
            if (check(personen,var)) {
                cout << "Winner is:"<< parteien[var];
                win = true;
                break;
            }
        }

        if (temp==1000) {
            ui();
            cout << "\n \n \n \n" << personenSize;
            Sleep(500);
            temp = 0;
        }
       temp++;

       int person = rand()% personenSize;

       if ((rand()% 1) == 0)  {
            int randomN = getPersonRandomNeigbor(person);
            personen[randomN] = personen[person];
       }

    }
    return 0;
}
