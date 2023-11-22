#ifndef BARREOCTOGONALE_H
#define BARREOCTOGONALE_H
#include "barre.h"

class BarreOctogonale : public Barre
{
private:
    int diametre;
public:
    BarreOctogonale(const string _ref, const int _longueur, const float _densite, const string _nom,
               const int _diametre);
    ~BarreOctogonale();
    float CalculerSection();
    float CalculerMasse();
};

#endif // BARREOCTOGONALE_H
