#ifndef CODEUR_H
#define CODEUR_H

class MccUldaq;

class Codeur
{
private:
    const MccUldaq &laCarte;

public:
    Codeur(const MccUldaq _laCarte);
};

#endif // CODEUR_H
