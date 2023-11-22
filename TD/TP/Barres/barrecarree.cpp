#include "barrecarree.h"

BarreCarree::BarreCarree(const string _ref, const int _longueur, const float _densite,
                         const string _nom, const int _cote)
    :Barre(_ref, _longueur, _densite, _nom), cote(_cote)
{
    cout << "Appel constructeur classe BarreCarree..." << endl;
}

BarreCarree::~BarreCarree()
{
    cout << "Appel destructeur classe BarreCarree..." << endl;
}

float BarreCarree::CalculerSection()
{
    float section = cote * cote;
    return section;
}

float BarreCarree::CalculerMasse()
{
    float masse = (longueur * CalculerSection() * densite) / 1000;
    return masse;
}
