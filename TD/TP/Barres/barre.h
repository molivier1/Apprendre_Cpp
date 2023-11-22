#ifndef BARRE_H
#define BARRE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Barre
{
private:
    string ref;
    string nom;
protected:
    int longueur;
    float densite;
public:
    Barre(const string _ref, const int _longueur, const float _densite, const string _nom);
    ~Barre();
    void AfficherCaracteristiques();
};

#endif // BARRE_H
