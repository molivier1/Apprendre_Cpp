#ifndef COMPTEBANCAIRE_H
#define COMPTEBANCAIRE_H

#include <iomanip>
#include <iostream>

class CompteBancaire
{
protected:
    float solde;
public:
    CompteBancaire(const float _solde = 0);
    void Deposer(const float _montant);
    bool Retirer(const float _montant);
    float ConsulterSolde();
};

#endif // COMPTEBANCAIRE_H
