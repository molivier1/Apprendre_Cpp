#ifndef MOTEUR_H
#define MOTEUR_H

class MccUldaq;

class Moteur
{
private:
    const MccUldaq &laCarte;
    int numCanal;
    double tensionMaxCommande;

public:
    Moteur(const MccUldaq &_laCarte, const int _numCanal, const double _tensionMaxCommande);
    ~Moteur();
    void FixerConsigneVitesse(const int _laConsigne);
};

#endif // MOTEUR_H
