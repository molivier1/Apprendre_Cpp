#include "jeu2048.h"

Jeu2048::Jeu2048()
{
    for (int i1 = 0; i1 < 4; i1++){
        for (int i2 = 0; i2 < 4; i2 ++){
            grille[i1][i2] = 0;
        }
    }

    srand(time(nullptr));
    PlacerNouvelleTuile();
}

void Jeu2048::ObtenirGrille(int _grille[4][4])
{
    for (int i1 = 0; i1 < 4; i1++){
        for (int i2 = 0; i2 < 4; i2 ++){
            _grille[i1][i2] = grille[i1][i2];
        }
    }
}

void Jeu2048::PlacerNouvelleTuile()
{
    int res;
    int x;
    int y;

    do{
        x = rand() % 4;
        y = rand() % 4;
        res = grille[x][y];
    } while (res != 0);

    grille[x][y] = (((rand() % 2) +1 ) * 2);
}

void Jeu2048::Deplacer(const char _direction)
{
    int ligne;
    int colonne;
    for(int indice = 0 ; indice < 4 ; indice++)
    {
        switch (_direction)
        {
        case 'G': // Cas Gauche
            for(ligne = 0 ; ligne < 4 ; ligne++)
            {
                for(colonne = 0 ; colonne < 3 ; colonne++)
                {
                    if(grille[ligne][colonne] == 0)
                    {
                        grille[ligne][colonne] = grille[ligne][colonne+1];
                        grille[ligne][colonne+1] = 0;
                    }
                }
            }
            break;

            // à poursuivre pour les autres cas
        case 'D': // Cas Droite
            for(ligne = 0 ; ligne < 4 ; ligne++)
            {
                for(colonne = 3 ; colonne > 0 ; colonne--)
                {
                    if(grille[ligne][colonne] == 0)
                    {
                        grille[ligne][colonne] = grille[ligne][colonne-1];
                        grille[ligne][colonne-1] = 0;
                    }
                }
            }
            break;

        case 'H': // Cas Haut
            for(ligne = 0 ; ligne < 3 ; ligne++)
            {
                for(colonne = 0 ; colonne < 4 ; colonne++)
                {
                    if(grille[ligne][colonne] == 0)
                    {
                        grille[ligne][colonne] = grille[ligne+1][colonne];
                        grille[ligne+1][colonne] = 0;
                    }
                }
            }
            break;

        case 'B': // Cas Bas
            for(ligne = 4 ; ligne > 0 ; ligne--)
            {
                for(colonne = 0 ; colonne < 4 ; colonne++)
                {
                    if(grille[ligne][colonne] == 0)
                    {
                        grille[ligne][colonne] = grille[ligne-1][colonne];
                        grille[ligne-1][colonne] = 0;
                    }
                }
            }
            break;
        }
    }
}

bool Jeu2048::Calculer(const char _direction)
{
    int ligne;
    int colonne;
    bool retour = false;
    for(int indice = 0 ; indice < 4 ; indice++)
    {
        switch (_direction)
        {
        case 'G': // Cas Gauche
            for(ligne = 0 ; ligne < 4 ; ligne++)
            {
                for(colonne = 0 ; colonne < 3 ; colonne++)
                {
                    if(grille[ligne][colonne] == grille[ligne][colonne+1])
                    {
                        grille[ligne][colonne] += grille[ligne][colonne+1];
                        grille[ligne][colonne+1] = 0;
                        retour = true;
                    }
                }
            }
            break;

            // à poursuivre pour les autres cas
        case 'D': // Cas Droite
            for(ligne = 0 ; ligne < 4 ; ligne++)
            {
                for(colonne = 3 ; colonne > 0 ; colonne--)
                {
                    if(grille[ligne][colonne] == grille[ligne][colonne-1])
                    {
                        grille[ligne][colonne] += grille[ligne][colonne-1];
                        grille[ligne][colonne-1] = 0;
                        retour = true;
                    }
                }
            }
            break;

        case 'H': // Cas Haut
            for(ligne = 0 ; ligne < 3 ; ligne++)
            {
                for(colonne = 0 ; colonne < 4 ; colonne++)
                {
                    if(grille[ligne][colonne] == grille[ligne+1][colonne])
                    {
                        grille[ligne][colonne] += grille[ligne+1][colonne];
                        grille[ligne+1][colonne] = 0;
                        retour = true;
                    }
                }
            }
            break;

        case 'B': // Cas Bas
            for(ligne = 4 ; ligne > 0 ; ligne--)
            {
                for(colonne = 0 ; colonne < 4 ; colonne++)
                {
                    if(grille[ligne][colonne] == grille[ligne-1][colonne])
                    {
                        grille[ligne][colonne] += grille[ligne-1][colonne];
                        grille[ligne-1][colonne] = 0;
                        retour = true;
                    }
                }
            }
            break;
        }
    }
    Deplacer(_direction);
    return retour;
}

int Jeu2048::CalculerScore()
{
    int somme = 0;
    for(int i1 = 0; i1 < 4; i1++){
        for(int i2 = 0; i2 <4; i2++){
            somme += grille[i1][i2];
        }
    }
    return somme;
}

Jeu2048::ETATS_DU_JEU Jeu2048::RechercherFinDePartie()
{
    int result = 0;
    ETATS_DU_JEU retour = EN_COURS;
    int ligne;
    int colonne;
    int verif = 0;

    for (int ligne = 0; ligne < 4; ligne++){
        for (int colonne = 0; colonne <4; colonne++){
            if(grille[ligne][colonne] != 0){
                result++;
            }

            if(grille[ligne][colonne] >= 2048){
                retour = GAGNE;
                break;
            }
        }
    }

    if(result >= 16)
    {
        // TEST GAUCHE
        for(ligne = 0 ; ligne < 4 ; ligne++)
        {
            for(colonne = 0 ; colonne < 3 ; colonne++)
            {
                if(grille[ligne][colonne] == grille[ligne][colonne+1])
                {
                    verif += 1;
                    //break;
                }
            }
        }

        // TEST DROITE
        for(ligne = 0 ; ligne < 4 ; ligne++)
        {
            for(colonne = 3 ; colonne > 0 ; colonne--)
            {
                if(grille[ligne][colonne] == grille[ligne][colonne-1])
                {
                    verif += 1;
                    //break;
                }
            }
        }

        // TEST HAUT
        for(ligne = 0 ; ligne < 3 ; ligne++)
        {
            for(colonne = 0 ; colonne < 4 ; colonne++)
            {
                if(grille[ligne][colonne] == grille[ligne+1][colonne])
                {
                    verif += 1;
                    //break;
                }
            }
        }

        // TEST BAS
        for(ligne = 4 ; ligne > 0 ; ligne--)
        {
            for(colonne = 0 ; colonne < 4 ; colonne++)
            {
                if(grille[ligne][colonne] == grille[ligne-1][colonne])
                {
                    verif += 1;
                    //break;
                }
            }
        }

        if (verif == 0){
            retour = PERDU;
        }

    }



    return retour;
}

bool Jeu2048::VerifCalculer(const char _direction)
{
    bool retour = true;
    int ligne;
    int colonne;
    int result = 0;

    for (ligne = 0; ligne < 4; ligne++){
        for (colonne = 0; colonne <4; colonne++){
            if(grille[ligne][colonne] != 0){
                result++;
            }
        }
    }

    if (result >= 16)
    {
        switch(_direction){
        case 'G':
            // TEST GAUCHE
            for(ligne = 0 ; ligne < 4 ; ligne++)
            {
                for(colonne = 0 ; colonne < 3 ; colonne++)
                {
                    if(grille[ligne][colonne] == grille[ligne][colonne+1])
                    {
                        return true;
                    }
                }
            }
            cout << "Déplacement invalide !" << endl;
            return false;
            break;

        case 'D':
            // TEST DROITE
            for(ligne = 0 ; ligne < 4 ; ligne++)
            {
                for(colonne = 3 ; colonne > 0 ; colonne--)
                {
                    if(grille[ligne][colonne] == grille[ligne][colonne-1])
                    {
                        return true;
                    }
                }
            }
            cout << "Déplacement invalide !" << endl;
            return false;
            break;

        case 'H':
            // TEST HAUT
            for(ligne = 0 ; ligne < 3 ; ligne++)
            {
                for(colonne = 0 ; colonne < 4 ; colonne++)
                {
                    if(grille[ligne][colonne] == grille[ligne+1][colonne])
                    {
                        return true;
                    }
                }
            }
            cout << "Déplacement invalide !" << endl;
            return false;
            break;

        case 'B':
            // TEST BAS
            for(ligne = 4 ; ligne > 0 ; ligne--)
            {
                for(colonne = 0 ; colonne < 4 ; colonne++)
                {
                    if(grille[ligne][colonne] == grille[ligne-1][colonne])
                    {
                        return true;
                    }
                }
            }
            cout << "Déplacement invalide !" << endl;
            return false;
            break;
        }
    }
    return retour;
}
