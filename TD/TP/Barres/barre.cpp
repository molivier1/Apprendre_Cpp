#include "barre.h"

Barre::Barre(const string _ref, const int _longueur,
             const float _densite, const string _nom)
    :ref(_ref), longueur(_longueur), densite(_densite), nom(_nom)
{
    cout << "Appel constructeur classe Barre..." << endl;
}

void Barre::AfficherCaracteristiques(){
    cout << "Appel methode AfficherCaracteristiques : " << this->ref << " " <<
            this->longueur << " " << this->densite << " " << this->nom << endl;
}

Barre::~Barre()
{
    cout << "Appel destructeur classe Barre..." << endl;
}
