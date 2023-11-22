#ifndef JEU2048_H
#define JEU2048_H

#include <math.h>
#include <time.h>
#include <iomanip>
#include <iostream>

using namespace std;

class Jeu2048
{
private:
    int grille[4][4];
public:
    Jeu2048();
    void PlacerNouvelleTuile();
    bool Calculer(const char _direction);
    void Deplacer(const char _direction);
    int CalculerScore();
    void ObtenirGrille(int _grille[4][4]);
    bool VerifCalculer(const char _direction);

    enum ETATS_DU_JEU
    {
        EN_COURS = 1,
        PERDU,
        GAGNE
    };

    ETATS_DU_JEU RechercherFinDePartie();
};

#endif // JEU2048_H
