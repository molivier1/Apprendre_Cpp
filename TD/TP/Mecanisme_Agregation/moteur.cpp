#include "moteur.h"
// #include "mcculdaq.h"

Moteur::Moteur(const MccUldaq &_laCarte, const int _numCanal, const double _tensionMaxCommande) : laCarte(_laCarte),
                                                                                                  numCanal(_numCanal),
                                                                                                  tensionMaxCommande(_tensionMaxCommande) // initialisation de la relation d'agrégation
{
    // laCarte.ulAOut(numCanal,0);
}

Moteur::~Moteur()
{
}