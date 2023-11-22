#include "barreronde.h"

BarreRonde::BarreRonde(const string _ref, const int _longueur, const float _densite, const string _nom,
                       const int _diametre)
    :Barre(_ref, _longueur, _densite, _nom), diametre(_diametre)
{
    cout << "Appel constructeur classe BarreRonde..." << endl;
}

BarreRonde::~BarreRonde()
{
    cout << "Appel destructeur classe BarreRonde..." << endl;
}

float BarreRonde::CalculerSection()
{
    float section = (M_PI * (diametre * diametre)) / 4;
    return section;
}

float BarreRonde::CalculerMasse()
{
    float masse = (longueur * CalculerSection() * densite) / 1000;
    return masse;
}
