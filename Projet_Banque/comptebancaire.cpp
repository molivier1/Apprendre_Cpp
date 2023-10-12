#include "comptebancaire.h"

using namespace std;

/**
 * @brief CompteBancaire::CompteBancaire (Constructeur)
 * @param _solde le solde a donné lors de l'initialisation de l'objet.
 */
CompteBancaire::CompteBancaire(float _solde):solde(_solde)
{

}

/**
 * @brief CompteBancaire::Deposer
 * @param _montant somme à déposer
 * @details Permet d'ajouter une somme au solde du compte bancaire
 */
void CompteBancaire::Deposer(float _montant)
{
    solde += _montant;
    cout << _montant <<" a été déposé au compte bancaire !" << endl;
}

/**
 * @brief CompteBancaire::Retirer
 * @param _montant somme à retirer
 * @return True si l'opération est possible. False si l'opération est impossible.
 * @details Permet de retirer une somme du compte bancaire si l'opération est possible.
 */
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

/**
 * @brief CompteBancaire::ConsulterSolde
 * @return le solde en float
 * @details Permet de consulter le solde du compte bancaire.
 */
float CompteBancaire::ConsulterSolde()
{
    return solde;
}
