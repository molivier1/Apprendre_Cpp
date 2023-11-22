#ifndef BARRECARREE_H
#define BARRECARREE_H
#include "barre.h"

class BarreCarree : public Barre
{
private:
    int cote;
public:
    BarreCarree(const string _ref, const int _longueur, const float _densite,
                const string _nom, const int _cote);
    ~BarreCarree();
    float CalculerSection();
    float CalculerMasse();
};

#endif // BARRECARREE_H
