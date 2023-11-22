#include "vecteur.h"
#include <iostream>

using namespace std;

Vecteur::Vecteur(const int _x, const int _y):
    x(_x),
    y(_y)
{

}



Vecteur Vecteur::operator+(const Vecteur &_autre)
{
    return Vecteur(x +_autre.x, y + _autre.y);
}

bool Vecteur::operator==(const Vecteur &_autre)
{
    bool retour = false;
    if(x == _autre.x && y == _autre.y)
        retour = true;
    return retour;
}

void Vecteur::Afficher()
{
    cout << "(" << x << "," << y << ")" << endl;
}

Vecteur Vecteur::operator+=(const Vecteur &_autre)
{
    return Vecteur((x +=_autre.x), (y += _autre.y));
}

Vecteur Vecteur::operator-(const Vecteur &_autre)
{
    return Vecteur(x -_autre.x, y - _autre.y);
}

Vecteur Vecteur::operator-=(const Vecteur &_autre)
{
    return Vecteur(x -=_autre.x, y -= _autre.y);
}

Vecteur Vecteur::operator*(const Vecteur &_autre)
{
    return Vecteur(x *_autre.x, y * _autre.y);
}

Vecteur Vecteur::operator*=(const Vecteur &_autre)
{
    return Vecteur(x *=_autre.x, y *= _autre.y);
}
