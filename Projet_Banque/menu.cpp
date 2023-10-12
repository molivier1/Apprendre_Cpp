#include "menu.h"

Menu::Menu(const string &_nom):nom(_nom), longueurMax(0)
{
    // ouvrir le fichier -> Création du flux en lecture
    ifstream leFichier(nom.c_str());
    // Si il y a une erreur
    if(!leFichier.is_open())
    {
        // alors Afficher un message indiquant une erreur de lecture
        cerr << "Erreur lors de l'ouverture du fichier" << endl;
        // et mettre nbOptions à 0
        nbOptions = 0;
    }
    else
    {
        // Sinon calculer nbOptions, le nombre d’options dans le fichier
        nbOptions = static_cast<int>(count(istreambuf_iterator<char>(leFichier),
                                           istreambuf_iterator<char>(),'\n'));
        leFichier.seekg(0,ios::beg);
        // allouer dynamiquement le tableau options en fonction de nbOptions
        options = new string[nbOptions];
        // Pour chaque option dans le fichier
        for(int i = 0; i < nbOptions; i++)
        {
            // Lire l’option et l’affecter dans le tableau options
            getline(leFichier, options[i]);
            // Si la taille de l’option est plus grande que longueurMax
            if(options[i].length() > longueurMax)
            {
                // alors longueurMax reçoit la taille de l’option
                longueurMax = options[i].length();
            } // FinSi
        } // FinPour
    } // FinSi
}

Menu::~Menu()
{
    delete [] options;
}

int Menu::Afficher()
{
    int choix;
    // Première ligne
    cout << "+" << setfill('-') << setw(4) << right << "+" << setw(23) << "+" << endl;
    // Lignes données
    for(int i = 0; i < nbOptions; i++)
    {
        cout << "| " << setw(2) << setfill(' ') << left << i+1  << setw(2) << "|" << setw(21)
             << options[i] << setw(2) << "|" << endl;
    }
    // Dernière ligne
    cout << "+" << setfill('-') << setw(4) << right << "+" << setw(23) << "+" << endl;
    // Test + entrée du choix
    cout << "\nEntrez un nombre entre 1 et " << nbOptions << " : ";
    if(!(cin>>choix))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choix = -1;
    }
    return choix;
}

void Menu::AttendreAppuiTouche()
{
    string chaine;
    cout << endl << "appuyer sur la touche Entrée pour continuer...";
    getline(cin,chaine);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("clear");
}
