#include <iostream>
#include <iomanip>
#include "ipv4.h"

using namespace std;

void AfficherTableau(const unsigned char *tab);
int main()
{
    unsigned char adresse[4]= {192,168,1,1};
    unsigned char masque[4];
    unsigned char reseau[4];
    unsigned char diffusion[4];
    unsigned char premiereAdresse[4];
    unsigned char derniereAdresse[4];
    IPv4 uneAdresse(adresse, 24); // instanciation de la classe IPv4
    cout << "Adresse IPv4 : ";
    AfficherTableau(adresse);
    uneAdresse.ObtenirMasque(masque); // appel d'une méthode
    cout << "Masque : ";
    AfficherTableau(masque);
    uneAdresse.ObtenirAdresseReseau(reseau);
    cout << "Réseau : ";
    AfficherTableau(reseau);
    uneAdresse.ObtenirAdresseDiffusion(diffusion);
    cout << "Diffusion : ";
    AfficherTableau(diffusion);
    uneAdresse.ObtenirPremiereAdresse(premiereAdresse);
    cout << "Première adresse : ";
    AfficherTableau(premiereAdresse);
    uneAdresse.ObtenirDerniereAdresse(derniereAdresse);
    cout << "Dernière adresse : ";
    AfficherTableau(derniereAdresse);
    cout << "Nombre de machines dans le réseau : " << uneAdresse.ObtenirNombreMachine() << endl;
    return 0;
}

IPv4::IPv4(const unsigned char * _adresse,const unsigned char _cidr)
{
    adresse = new unsigned char [4];
    masque = new unsigned char [4];
    for(int indice = 0 ; indice < 4 ; indice++)
        adresse[indice] = _adresse[indice];
    if(_cidr <= 32)
        CalculerMasque(_cidr);
}
IPv4::IPv4(const unsigned char * _adresse,const unsigned char * _masque)
{
    adresse = new unsigned char [4];
    masque = new unsigned char [4];
    for(int indice = 0 ; indice < 4 ; indice++)
    {
        adresse[indice] = _adresse[indice];
        masque[indice] = _masque[indice];
    }
}
IPv4::~IPv4()
{
    delete [] adresse;
    delete [] masque ;
}

void IPv4::CalculerMasque(unsigned char _cidr)
{
    int indice ;
    // Le masque est remis à 0 -> 0.0.0.0
    for(indice = 0 ; indice < 4 ; indice++)
        masque[indice] = 0 ;
    indice = 0;
    // tant que le cidr est un multiple de 8
    while(_cidr >= 8)
    {
        masque[indice++] = 255 ;
        _cidr -= 8 ;
    }
    // Complément pour la fin du cidr (<8)
    unsigned char puissance = 128 ;
    while(_cidr-- > 0) // Après le test la variable _cidr est décrémentée
    { // les puissances de 2 sont ajoutées à l'octet par valeur décroissante
        masque[indice] += puissance ;
        puissance /=2 ;
    }
}

void IPv4::ObtenirMasque(unsigned char * _masque)
{
    for(int indice = 0 ; indice < 4 ; indice++)
        _masque[indice] = masque[indice];
}

void IPv4::ObtenirAdresseReseau(unsigned char * _reseau)
{
    for(int indice = 0 ; indice < 4 ; indice++)
        _reseau[indice] = adresse[indice] & masque[indice] ;
}

void IPv4::ObtenirAdresseDiffusion(unsigned char *_diffusion)
{
    unsigned char adresseDuReseau[4];
    ObtenirAdresseReseau(adresseDuReseau);
    for(int indice = 0 ; indice < 4 ; indice++)
        _diffusion[indice] = adresseDuReseau[indice] | ~masque[indice] ;
}

void AfficherTableau(const unsigned char *tab)
{
    for(int indice=0 ; indice < 4 ; indice ++)
    {
        cout << static_cast<int> (tab[indice]);
        if(indice < 3)
            cout << "." ;
    }
    cout << endl;
}

void IPv4::ObtenirPremiereAdresse(unsigned char * _premiereAdresse)
{
    int i;
    unsigned char adresseDuReseau[4];
    ObtenirAdresseReseau(adresseDuReseau);
    for(i=0;i<4;i++){
        _premiereAdresse[i] = adresseDuReseau[i];
    }
    _premiereAdresse[3] += 1;
}

void IPv4::ObtenirDerniereAdresse(unsigned char * _derniereAdresse)
{
    int i;
    unsigned char adresseDeDiffusion[4];
    ObtenirAdresseDiffusion(adresseDeDiffusion);
    for(i=0;i<4;i++){
        _derniereAdresse[i] = adresseDeDiffusion[i];
    }
    _derniereAdresse[3] -= 1;
}

int IPv4::ObtenirNombreMachine()
{
    int nombre;
    unsigned char premiereAdresse[4];
    ObtenirPremiereAdresse(premiereAdresse);
    unsigned char adresseDeDiffusion[4];
    ObtenirAdresseDiffusion(adresseDeDiffusion);
    nombre = adresseDeDiffusion[3] - premiereAdresse[3];
    return nombre;
}
