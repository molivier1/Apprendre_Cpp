#include "equilibreuse.h"

Equilibreuse::Equilibreuse() : leMoteur(nullptr), leCodeur(nullptr)
{
    leMoteur = new Moteur(laCarte, 1, 4.0);
    leCodeur = new Codeur(laCarte);
}

Equilibreuse::~Equilibreuse()
{
    if (leMoteur != nullptr)
    {
        delete leMoteur;
    }

    if (leCodeur != nullptr)
    {
        delete leCodeur;
    }
}