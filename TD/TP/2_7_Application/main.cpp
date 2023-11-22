#include "menu.h"

int main()
{
    int choix;
    Menu menu("../2_7_Application/menu.txt");
    do{
        choix = menu.Afficher();
        string choisiOption = "Vous avez choisi l'option n'";
        switch (choix)
        {
        case OPTION_1:
            cout << choisiOption << choix << endl;
            Menu::AttendreAppuiTouche();
            break;

        case OPTION_2:
            cout << choisiOption << choix << endl;
            Menu::AttendreAppuiTouche();
            break;

        case OPTION_3:
            cout << choisiOption << choix << endl;
            Menu::AttendreAppuiTouche();
            break;

        case OPTION_4:
            cout << choisiOption << choix << endl;
            Menu::AttendreAppuiTouche();
            break;

        case QUITTER:
            cout << choisiOption << choix << endl;
            Menu::AttendreAppuiTouche();
            break;

        default :
            cout << "Le choix n'est pas valide !" << endl;
            Menu::AttendreAppuiTouche();
            break;
        }
    }
    while(choix != QUITTER);
    return 0;
}
