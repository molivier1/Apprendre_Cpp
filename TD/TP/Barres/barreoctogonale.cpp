#include "barreoctogonale.h"

BarreOctogonale::BarreOctogonale(const string _ref, const int _longueur, const float _densite,
                                 const string _nom, const int _diametre)
:Barre(_ref, _longueur, _densite, _nom), diametre(_diametre)
{
    cout << "Appel constructeur classe BarreOctogonale..." << endl;
}

BarreOctogonale::~BarreOctogonale()
{
    cout << "Appel destructeur classe BarreOctogonale..." << endl;
}

float BarreOctogonale:: CalculerSection()
{
    float section = 2 * (diametre * diametre) * (sqrt(2) - 1);
    return section;
}

float BarreOctogonale::CalculerMasse()
{
    float masse = (longueur * CalculerSection() * densite) / 1000;
    return masse;
}
