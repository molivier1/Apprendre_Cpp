#include "comptebancaire.h"

using namespace std;

CompteBancaire::CompteBancaire(float _solde):solde(_solde)
{

}

void CompteBancaire::Deposer(float _montant)
{
    solde += _montant;
    cout << _montant <<" a été déposé au compte bancaire !" << endl;
}

bool CompteBancaire::Retirer(float _montant)
{
    if (solde >= _montant)
    {
        solde -= _montant;
        cout << _montant <<" a été retiré du compte bancaire !" << endl;
        return true;
    }
    else
    {
        cout << "Impossible de faire ce retrait d'argent !" << endl;
        return false;
    }
}

float CompteBancaire::ConsulterSolde()
{
    return solde;
}
