#include <QCoreApplication>
#include "jeu2048.h"
#include "plateau.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Plateau plateau;

    bool retour;
    plateau.Afficher();
    do {
        retour = plateau.JouerCoup();
    } while(retour != true);

    if(retour == true){
        return EXIT_SUCCESS;
    }

    return a.exec();
}
