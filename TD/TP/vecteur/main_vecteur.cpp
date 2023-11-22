#include <iostream>
#include "vecteur.h"

using namespace std;

int main()
{
    Vecteur va(4,4);
    Vecteur vb(4,1);
    Vecteur resultat;
    resultat = va + vb;
    cout << "Addition de base : ";
    resultat.Afficher();
    cout << "operator== pour va == vb : " << va.operator==(vb) << endl;
    cout << "operator+ pour va + vb : ";
    va.operator+(vb).Afficher();
    cout << "operator+= pour va += vb : ";
    va.operator+=(vb).Afficher();
    cout << "operator- pour va - vb : ";
    va.operator-(vb).Afficher();
    cout << "operator-= pour va -= vb : ";
    va.operator-=(vb).Afficher();
    cout << "operator* pour va * vb : ";
    va.operator-=(vb).Afficher();
    cout << "operator*= pour va *= vb : ";
    va.operator-=(vb).Afficher();
    return 0;
}
