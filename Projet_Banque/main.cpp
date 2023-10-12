#include "menu.h"
#include "comptebancaire.h"

using namespace std;

int main()
{
    float montant;
    int sortie = 0;
    CompteBancaire compteBancaire(100);
    Menu menu("/home/USERS/ELEVES/SNIR2022/molivier/Documents/SNIR2/Code/C++/Apprendre_Cpp/Projet_Banque/compteBancaire.txt");
    do
    {
        switch(menu.Afficher())
        {
        case 1:
            cout << "Solde du compte : " << compteBancaire.ConsulterSolde() << endl;
            menu.AttendreAppuiTouche();
            break;
        case 2:
            cout << "Rentrez un montant à déposer : ";
            cin >> montant;
            compteBancaire.Deposer(montant);
            menu.AttendreAppuiTouche();
            break;
        case 3:
            cout << "Rentrez un montant à retirer : ";
            cin >> montant;
            compteBancaire.Retirer(montant);
            menu.AttendreAppuiTouche();
            break;
        case 4:
            sortie = 1;
            cout << "Au revoir." << endl;
            break;
        default:
            cout << "Entrée invalide !" << endl;
            menu.AttendreAppuiTouche();
            break;
        }
    } while(sortie == 0);

    return EXIT_SUCCESS;
}
