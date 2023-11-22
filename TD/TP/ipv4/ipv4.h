#ifndef _IPV4_H
#define _IPV4_H
class IPv4
{
private:
    unsigned char * adresse;
    unsigned char * masque ;
    void CalculerMasque(const unsigned char _cidr); // _cidr est utilisé en tant que variable localedans la méthode (pas de const devant)
public:
    IPv4(const unsigned char * _adresse, const unsigned char _cidr);
    IPv4(const unsigned char * _adresse, const unsigned char * _masque);
    ~IPv4();
    void ObtenirMasque(unsigned char * _masque);
    void ObtenirAdresseReseau(unsigned char * _reseau);
    void ObtenirAdresseDiffusion(unsigned char * _diffusion);
    void ObtenirPremiereAdresse(unsigned char * _premiereAdresse);
    void ObtenirDerniereAdresse(unsigned char * _derniereAdresse);
    int ObtenirNombreMachine();
};
#endif
