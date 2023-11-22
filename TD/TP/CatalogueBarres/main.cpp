#include "barre.h"
#include "barreronde.h"
#include "barrerectangle.h"
#include "barrecarree.h"
#include "barrehexagonale.h"
#include "barreoctogonale.h"
#include "catalogue.h"

using namespace std;

int main()
{
    Catalogue leCatalogue(5);
    BarreRonde b1("B1", 200, 8, "BarreRonde 1", 20);
    BarreCarree b2("B2", 200, 8, "BarreCarré 2", 20);
    leCatalogue.AjouterBarre(&b1);
    leCatalogue.AjouterBarre(&b2);
    leCatalogue.AfficherCatalogue();
    return EXIT_SUCCESS;
}
