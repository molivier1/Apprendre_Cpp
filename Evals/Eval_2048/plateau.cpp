#include "plateau.h"

Plateau::Plateau()
{
    nbCoups = 0;
    score = 0;
}

void Plateau::Afficher()
{
    int laGrille[4][4];
    system("clear");
    jeu.ObtenirGrille(laGrille);
    cout << "| Score : " << score << " | Nombre de coups : " << nbCoups << " |" << endl;
    cout << endl;
    for(int ligne = 0 ; ligne < 4 ; ligne++)
    {
        // affichage de ligne séparatrice
        cout << setw(4) << setfill(' ') <<
                "+" << setw(7) << setfill('-') <<
                "+" << setw(7) << setfill('-') <<
                "+" << setw(7) << setfill('-') <<
                "+" << setw(7) << setfill('-') << "+" << endl;
        // affichage d'une ligne de la grille
        // Valeur 1 : si == 0 alors vide
        cout << setw(4) << setfill(' ') << "|" << setw(5) << setfill(' ');
        if (laGrille[ligne][0] != 0){
            cout << laGrille[ligne][0];
        }
        else {
            cout << " ";
        }
        cout << setw(2) << setfill(' ') << "|";

        // Valeur 2 : si == 0 alors vide
        cout << setw(5) << setfill(' ');
        if(laGrille[ligne][1] != 0){
            cout << laGrille[ligne][1];
        }
        else {
            cout << " ";
        }
        cout << setw(2) << setfill(' ') << "|";

        // Valeur 3 : si == 0 alors vide
        cout << setw(5) << setfill(' ');
        if (laGrille[ligne][2] != 0){
            cout << laGrille[ligne][2];
        }
        else {
            cout << " ";
        }
        cout << setw(2) << setfill(' ') << "|";

        // Valeur 4 : si == 0 alors vide
        cout << setw(5) << setfill(' ');
        if (laGrille[ligne][3] != 0){
            cout << laGrille[ligne][3];
        }
        else {
            cout << " ";
        }
        cout << setw(2) << setfill(' ') << "|" << endl;
    }
    // affichage de la dernière ligne du tableau
    cout << setw(4) << setfill(' ') <<
            "+" << setw(7) << setfill('-') <<
            "+" << setw(7) << setfill('-') <<
            "+" << setw(7) << setfill('-') <<
            "+" << setw(7) << setfill('-') << "+" << endl;
    // affichage du texte sous le tableau
    cout << endl;
    cout << "F pour sortir du jeu" << endl;
    cout << "Votre déplacement : H (^), B (v), G (<-), D (->) : " << endl;
}

bool Plateau::JouerCoup()
{
    bool retour = false;
    Jeu2048::ETATS_DU_JEU etat = jeu.RechercherFinDePartie();
    switch(etat){
    case Jeu2048::EN_COURS:
        char touche;
        // Tant que la méthode VerifCalculer ne renvoie pas false alors, on redemande
        // à l'utilisateur de rentrer une touche.
        // Cette méthode va vérifier si le déplacement que l'utilisateur souhaite réaliser
        // est possible. Si le déplacement est valide, la méthode retourne true.
        // Dans le cas contraire, elle retourne false.
        do{
            cin  >> touche ;
            touche = toupper(touche);
        } while(jeu.VerifCalculer(touche) == false);

        if(strchr("BHGD",touche) != nullptr)
        {
            nbCoups++;
            jeu.Deplacer(touche);
            jeu.Calculer(touche);
            jeu.PlacerNouvelleTuile();
            score = jeu.CalculerScore();
            Afficher();
        }
        if(touche == 'F'){
            retour = true;
        }
        break;


    case Jeu2048::PERDU:
        cout << "Perdu ! Vous ne pouvez plus vous déplacer !" << endl;
        retour = true;
        break;


    case Jeu2048::GAGNE:
        cout << "Gagné !" << endl;
        retour = true;
        break;
    }



    return retour;
}
