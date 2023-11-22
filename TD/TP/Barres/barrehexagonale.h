#ifndef BARREHEXAGONALE_H
#define BARREHEXAGONALE_H
#include "barre.h"

class BarreHexagonale : public Barre
{
private:
    int diametre;
public:
    BarreHexagonale(const string _ref, const int _longueur, const float _densite, const string _nom,
               const int _diametre);
    ~BarreHexagonale();
    float CalculerSection();
    float CalculerMasse();
};

#endif // BARREHEXAGONALE_H
