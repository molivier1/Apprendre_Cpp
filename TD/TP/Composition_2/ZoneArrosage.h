#ifndef ZONEARROSAGE_H
#define ZONEARROSAGE_H

#include <iostream>
#include <string>

#include "vanne.h"

#define gpio_num_t int

class ZoneArrosage
{
private:
    Vanne laVanne;
    int numZone;

public:
    ZoneArrosage(int _numZone,
                 const gpio_num_t _commandeVanne,
                 const gpio_num_t _senseAVanne,
                 const gpio_num_t _senseBVanne,
                 const gpio_num_t _brocheHumidite);


    ZoneArrosage(const std::string _initialisationZone);


    void Piloter();
};
#endif // ZONEARROSAGE_H