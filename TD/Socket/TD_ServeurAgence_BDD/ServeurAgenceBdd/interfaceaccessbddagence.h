#ifndef INTERFACEACCESSBDDAGENCE_H
#define INTERFACEACCESSBDDAGENCE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonArray>
#include <QFileInfo>
#include <QSettings>
#include <QJsonObject>

#include "avion.h"

class InterfaceAccessBddAgence
{
public:
    InterfaceAccessBddAgence();

    void ajouterReservation(int ref, int idClient, int nroSiege);
    void supprimerReservation(int idResa);
    QList <avion *> obtenirListeDesVols();
    int ajouterClient(QString nom, QString prenom, QString email);
    QJsonArray obtenirListeReservations();

private:
    QSqlDatabase bdd;

    QString login;
    QString motDePasse;
    QString adresse;
    QString nomBase;

    void chargerParametresBdd();

    QList <int> obtenirListeDesPlacesOccupees(int refVol);
};

#endif // INTERFACEACCESSBDDAGENCE_H
