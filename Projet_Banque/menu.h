#ifndef MENU_H
#define MENU_H
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

class Menu
{
public:
    Menu(const string &_nom);
    ~Menu();
    int Afficher();
    static void AttendreAppuiTouche();

private:
    /// Nom du fichier à ouvrir pour créer le menu
    string nom;
    /// La plus grande longueur d'un item
    int longueurMax;
    /// Nombre d'items du menu
    int nbOptions;
    /// Pointeur sur tableau des items
    string *options;



};

class Exception
{
public:
    Exception(int _code, string _message);
    int ObtenirCodeErreur() const;
    string ObtenirMessage() const;

private:
    int code;
    string message;
};

#endif // MENU_H
