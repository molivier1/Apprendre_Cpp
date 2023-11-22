#ifndef BARRERONDE_H
#define BARRERONDE_H
#include "barre.h"

class BarreRonde : public Barre
{
private:
    int diametre;
public:
    BarreRonde(const string _ref, const int _longueur, const float _densite, const string _nom,
               const int _diametre);
    ~BarreRonde();
    float CalculerSection();
    float CalculerMasse();
};

#endif // BARRERONDE_H
