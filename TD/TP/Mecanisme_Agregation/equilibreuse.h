#ifndef EQUILIBREUSE_H
#define EQUILIBREUSE_H

#include "moteur.h"
#include "mcculdaq.h"
#include "codeur.h"

class Equilibreuse
{
private:
    MccUldaq laCarte;
    Moteur *leMoteur;
    Codeur *leCodeur;
public:
    Equilibreuse();
    ~Equilibreuse();
};

#endif // EQUILIBREUSE_H
