#ifndef VECTEUR_H
#define VECTEUR_H

class Vecteur
{
public:
    Vecteur(const int _x=0,const int _y=0);// ce premier constructeur initialise x et y avec les paramètres

    Vecteur operator+ (const Vecteur &_autre);
    bool operator==(const Vecteur &_autre);
    void Afficher();
    Vecteur operator+= (const Vecteur &_autre);
    Vecteur operator-(const Vecteur &_autre);
    Vecteur operator-=(const Vecteur &_autre);
    Vecteur operator*(const Vecteur &_autre);
    Vecteur operator*=(const Vecteur &_autre);
private:
    int x;
    int y;
};
#endif // VECTEUR_H
