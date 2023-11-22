#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class Menu
{
private:
    string nom;
    string *options;
    int nbOptions;
    size_t longueurMax;

public:
    Menu(const string &_nom); // Constructeur -> const "type" _"varName"
    ~Menu(); // Destructeur
    int Afficher();
    static void AttendreAppuiTouche();
};

enum CHOIX_MENU
{
    OPTION_1 = 1,
    OPTION_2,
    OPTION_3,
    OPTION_4,
    QUITTER
};

#endif // MENU_H
