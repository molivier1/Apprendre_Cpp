#ifndef PLATEAU_H
#define PLATEAU_H

#include "jeu2048.h"
#include <iomanip>
#include <iostream>
#include <syscall.h>
#include <cstring>

using namespace std;

class Plateau
{
private:
    int nbCoups;
    int score;
    Jeu2048 jeu;
public:
    Plateau();
    void Afficher();
    bool JouerCoup();
};

#endif // PLATEAU_H
