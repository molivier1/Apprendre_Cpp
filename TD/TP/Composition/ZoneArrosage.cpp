#include "ZoneArrosage.h"

ZoneArrosage::ZoneArrosage(const int _numZone, const int _commandeVanne, const int _senseAVanne,
                           const int _senseBVanne, const int _brocheHumidite) : laVanne(_commandeVanne, _senseAVanne, _senseBVanne),
    numZone(_numZone)
{
    // reste du code pour le constructeur
}

ZoneArrosage::ZoneArrosage(const std::string _initialisationZone)
{
    int parametres[4];
    size_t prec = 0;
    size_t pos = 0;
    for (int indice = 0; indice < 4; indice++)
    {
        pos = _initialisationZone.find(' ', prec);
        parametres[indice] = atoi(_initialisationZone.substr(prec, pos).c_str());
        prec = pos + 1; // on incrémente pos pour le tour d'après.
    }
    numZone = parametres[0];
    laVanne = new Vanne(parametres[1], parametres[2], parametres[3]);
}

ZoneArrosage::~ZoneArrosage()
{
    delete laVanne;
}
