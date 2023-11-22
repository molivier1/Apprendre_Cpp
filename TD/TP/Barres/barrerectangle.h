#ifndef BARRERECTANGLE_H
#define BARRERECTANGLE_H
#include "barre.h"

class BarreRectangle : public Barre
{
private:
    int hauteur;
    int largeur;
public:
    BarreRectangle(const string _ref, const int _longueur, const float _densite, const string _nom,
                   const int _hauteur, const int _largeur);
    ~BarreRectangle();
    float CalculerSection();
    float CalculerMasse();
};

#endif // BARRERECTANGLE_H
