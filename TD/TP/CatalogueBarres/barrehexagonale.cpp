#include "barrehexagonale.h"

BarreHexagonale::BarreHexagonale(const string _ref, const int _longueur, const float _densite,
                                 const string _nom, const int _diametre)
:Barre(_ref, _longueur, _densite, _nom), diametre(_diametre)
{
    cout << "Appel constructeur classe BarreHexagonale..." << endl;
}

BarreHexagonale::~BarreHexagonale()
{
    cout << "Appel destructeur classe BarreHexagonale..." << endl;
}


float BarreHexagonale:: CalculerSection()
{
    float section = (2 * sqrt(3)) * ((diametre * diametre) / 4);
    return section;
}

float BarreHexagonale::CalculerMasse()
{
    float masse = (longueur * CalculerSection() * densite) / 1000;
    return masse;
}
