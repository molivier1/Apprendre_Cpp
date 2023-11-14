#include "menu.h"
/**
 *  @author Philippe SIMIER
 *  @abstract Class pour créer un menu
 *  @date 11 septembre 2020
 */

using namespace std;

/**
 * @brief Menu::Menu (Constructeur)
 * @param _nom nom du fichier contenant les items du menu
 */

Menu::Menu(const string &_nom):
    nom(_nom),
    longueurMax(0),
    nbOptions(0),
    options(nullptr)
{
    ifstream fichierMenu(nom);
    if (fichierMenu.fail()){

        throw (std::runtime_error("Erreur d'ouverture du fichier"));

    }
    else{

        nbOptions = static_cast<int>(count(istreambuf_iterator<char>(fichierMenu),
                                           istreambuf_iterator<char>(),
                                           '\n'));
        fichierMenu.seekg(0,ios::beg);

        int longueur;
        string item;
        // allocation dynamique du tableaux création du tableau
        options = new string[nbOptions];
        // Lecture et chargement des items
        for( int i = 0; i < nbOptions ; i++){
            getline(fichierMenu, item);
            longueur = static_cast<int>(item.length());
            if (longueur > longueurMax)
                longueurMax = longueur;
            if (longueur > 0)            // si la ligne n'est pas vide
                options[i] = item;      // On l'ajoute au tableau
            else{                        // sinon on retire 1 du nb d'options
                nbOptions--;
                i--;
            }
        }

    }
}

/**
 * @brief Menu::~Menu (Destructeur)
 */

Menu::~Menu()
{
    if (options != nullptr)
        delete  [] options;
}

/**
 * @brief Menu::Afficher
 * @details Affiche le menu sur la console
 * @return int le code de l'item sélectionné
 */

int Menu::Afficher()
{
    int choix;
    // si le fichier ne peut pas être ouvert alors pas d'affichage;
    if (nbOptions == 0)
        choix = -1;
    else{
        cout << setfill('-');
        // dessine la première ligne du menu
        cout << "+-" << setw(4) << "-+-" << setw(longueurMax+2) << "-+" << endl;
        cout << setfill(' ');
        for( int i =0; i < nbOptions; i++){
            cout << "| " << i+1 << " | " << setw(longueurMax) << options[i]  << " |" << endl;
        }
        // dessine la dernière ligne
        std::cout << setfill('-');
        cout << "+-" << setw(4) << "-+-" << setw(longueurMax+2) << "-+" << endl;
        cout << setfill(' ');

        do{
            cout << "Votre choix entre 1 et " << nbOptions << " : ";
            if(!(cin>>choix))
            {
                cin. clear();
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
                choix = -1;
            }

        }while (  choix > nbOptions);

    }

    return choix;
}

/**
 * @brief Menu::AttendreAppuiTouche
 * @abstract Méthode statique pour attendre l'appui sur une touche du clavier.
 *           Le buffer d'entrée est vidé, l'écran est effacé après l'action sur le clavier
 */

void Menu::AttendreAppuiTouche()
{
    string uneChaine;
    cout << endl << "Appuyer sur la touche Entrée pour continuer ...";
    getline(cin,uneChaine);
    // Vidage du tampon d'entrée
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#else

#endif
}

Exception::Exception(int _code, string _message):
    code(_code),
    message(_message)
{}

int Exception::ObtenirCodeErreur() const
{
    return code;
}

string Exception::ObtenirMessage() const
{
    return message;
}
