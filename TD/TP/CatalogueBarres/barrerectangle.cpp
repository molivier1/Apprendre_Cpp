#include "barrerectangle.h"

BarreRectangle::BarreRectangle(const string _ref, const int _longueur, const float _densite,
                               const string _nom, const int _hauteur, const int _largeur)
    :Barre(_ref, _longueur, _densite, _nom), hauteur(_hauteur), largeur(_largeur)
{
    cout << "Appel constructeur classe BarreRectangle..." << endl;
}

BarreRectangle::~BarreRectangle()
{
    cout << "Appel destructeur classe BarreRectangle..." << endl;
}

float BarreRectangle::CalculerSection()
{
    float section = largeur * hauteur;
    return section;
}

float BarreRectangle::CalculerMasse()
{
    float masse = (longueur * CalculerSection() * densite) / 1000;
    return masse;
}
