#include "barre.h"
#include "barreronde.h"
#include "barrerectangle.h"
#include "barrecarree.h"
#include "barrehexagonale.h"
#include "barreoctogonale.h"

using namespace std;

int main()
{
    // Barre
    Barre *barre = new Barre("jeSuisLaRefBarre", 1, 8.96, "jeSuisUneBarre");
    barre->AfficherCaracteristiques();
    delete barre;
    cout << endl;

    // BarreRonde
    BarreRonde *barreRonde = new BarreRonde("jeSuisLaRefBarreRonde", 1, 8.96, "jeSuisUneBarreRonde", 5);
    barreRonde->AfficherCaracteristiques();
    cout << "Section barreRonde : " << barreRonde->CalculerSection() << " mm²" << endl;
    cout << "Masse barreRonde : " << barreRonde->CalculerMasse() << " kg" << endl;
    delete barreRonde;
    cout << endl;

    // BarreRectangle
    BarreRectangle *barreRectangle = new BarreRectangle("jeSuisLaRefBarreRectangle",
                                                        1, 8.96, "jeSuisUneBarreRectangle", 5, 5);
    barreRectangle->AfficherCaracteristiques();
    cout << "Section barreRectangle : " << barreRectangle->CalculerSection() << " mm²" << endl;
    cout << "Masse barreRectangle : " << barreRectangle->CalculerMasse() << " kg" << endl;
    delete barreRectangle;
    cout << endl;

    // BarreCarree
    BarreCarree *barreCarree = new BarreCarree("jeSuisLaRefBarreCarree", 1, 8.96, "jeSuisUneBarreCarree", 5);
    barreCarree->AfficherCaracteristiques();
    cout << "Section barreCarree : " << barreCarree->CalculerSection() << " mm²" << endl;
    cout << "Masse barreCarre : " << barreCarree->CalculerMasse() << " kg"  << endl;
    delete barreCarree;
    cout << endl;

    // BarreHexagonale
    BarreHexagonale *barreHexagonale = new BarreHexagonale("jeSuisLaRefBarreHexagonale",
                                                           1, 8.96, "jeSuisUneBarreHexagonale", 5);
    barreHexagonale->AfficherCaracteristiques();
    cout << "Section barreHexagonale : " << barreHexagonale->CalculerSection() << " mm²" << endl;
    cout << "Masse barreHexagonale : " << barreHexagonale->CalculerMasse() << " kg"  << endl;
    delete barreHexagonale;
    cout << endl;

    // BarreOctogonale
    BarreOctogonale *barreOctogonale = new BarreOctogonale("jeSuisLaRefBarreOctogonale",
                                                           1, 8.96, "jeSuisUneBarreOctogonale", 5);
    barreOctogonale->AfficherCaracteristiques();
    cout << "Section barreOctogonale : " << barreOctogonale->CalculerSection() << " mm²" << endl;
    cout << "Masse barreOctogonale : " << barreOctogonale->CalculerMasse() << " kg"  << endl;
    delete barreOctogonale;
    cout << endl;
    return EXIT_SUCCESS;
}
