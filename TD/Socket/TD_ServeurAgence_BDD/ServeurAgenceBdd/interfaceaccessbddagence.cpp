#include "interfaceaccessbddagence.h"

InterfaceAccessBddAgence::InterfaceAccessBddAgence()
{
    chargerParametresBdd();

    bdd = QSqlDatabase::addDatabase("QMYSQL");
    bdd.setHostName(adresse);
    bdd.setDatabaseName(nomBase);
    bdd.setUserName(login);
    bdd.setPassword(motDePasse);

    if (!bdd.open())
    {
        qDebug() << "Erreur connection bdd " << bdd.lastError().text();
    }
    else
    {
        qDebug() << "Ouverture de la base de donnée " << bdd.databaseName();
    }
}

void InterfaceAccessBddAgence::ajouterReservation(int ref, int idClient, int nroSiege)
{
    QSqlQuery ajoutReservation;
    // préparer la requete d'ajout du client
    /* a completer */
    ajoutReservation.prepare("insert into reservations (referenceVol, idClient, numeroSiege) "
                             "values (:ref, :idClient, :nroSiege);");

    ajoutReservation.bindValue(":ref", ref);
    ajoutReservation.bindValue(":idClient", idClient);
    ajoutReservation.bindValue(":nroSiege", nroSiege);

    if (!ajoutReservation.exec())
    {
        qDebug()<<ajoutReservation.lastError().text();
    }
}

void InterfaceAccessBddAgence::supprimerReservation(int idResa)
{
    QSqlQuery supprimeReservation;
    // préparer la requete d'ajout du client
    /* a completer */
    supprimeReservation.prepare("delete from reservations where idResa = :idResa;");

    supprimeReservation.bindValue(":idResa", idResa);

    if (!supprimeReservation.exec())
    {
        qDebug()<<supprimeReservation.lastError().text();
    }
}

QList<avion *> InterfaceAccessBddAgence::obtenirListeDesVols()
{
    QList<avion *>lesVols;
    QSqlQuery requete(/* a completer */);
    while(requete.next())
    {
        avion *a=new avion;
        a->infosVol.reference=requete.value("reference").toInt();
        a->infosVol.denomination=requete.value("denomination").toString();
        a->siegesOccupees=obtenirListeDesPlacesOccupees(a->infosVol.reference);
        lesVols.append(a);
    }
    return lesVols;
}

int InterfaceAccessBddAgence::ajouterClient(QString nom, QString prenom, QString email)
{
    QSqlQuery requetePreparee;
    int idClient=-1;
    // obtenir l'id du client en fonction de son email
    /* a completer */
    requetePreparee.prepare("select id from clients where email = :mail;");

    requetePreparee.bindValue(":mail", email);

    if (!requetePreparee.exec())
    {
        qDebug()<<requetePreparee.lastError().text();
    }
    else // requete syntaxiquement ok
    {
        if (requetePreparee.size()!=0) // le client existe deja
        {
            // recupérer le résultat de la requete et le mettre dans idClient
            /* a completer */
            while(requetePreparee.next())
            {
                idClient = requetePreparee.value("id").toInt();
            }
        }
        else // le client n'existe pas
        {
            QSqlQuery ajoutClient;
            // préparer la requete d'ajout du client
            /* a completer */
            ajoutClient.prepare("insert into clients (nom, prenom, email) "
                                "values (:nom, :prenom, :email);");

            ajoutClient.bindValue(":nom", nom);
            ajoutClient.bindValue(":prenom", prenom);
            ajoutClient.bindValue(":email", email);

            if (!ajoutClient.exec())
            {
                qDebug()<<ajoutClient.lastError().text();
            }
            else // si la requete a abouti, obtenir l'id et la mettre dans idClient
            {
                idClient=ajoutClient.lastInsertId().toInt();
            }
        }
    }
    return idClient;
}

QJsonArray InterfaceAccessBddAgence::obtenirListeReservations()
{

}

void InterfaceAccessBddAgence::chargerParametresBdd()
{
    QString nomFichierIni = "../ServeurAgenceBdd/ServeurAgenceBdd.ini";
    QFileInfo fichierIni(nomFichierIni);
    if (fichierIni.exists() && fichierIni.isFile())
    {
        QSettings param(nomFichierIni,QSettings::IniFormat);
        adresse = param.value("BDD/adresseIp").toString();
        nomBase = param.value("BDD/nomDeLaBase").toString();
        login = param.value("BDD/login").toString();
        motDePasse = param.value("BDD/motDePasse").toString();
    }
}

QList<int> InterfaceAccessBddAgence::obtenirListeDesPlacesOccupees(int refVol)
{
    QList <int>places;
    QSqlQuery requetePreparee;
    /* a completer */
    requetePreparee.prepare("select numeroSiege from reservations where referenceVol = :refVol;");

    requetePreparee.bindValue(":refVol", refVol);
    if (!requetePreparee.exec())
    {
        qDebug()<<requetePreparee.lastError().text();
    }
    else
    {
        while(requetePreparee.next())
        {
            places.append(requetePreparee.value("numeroSiege").toInt());
        }
    }
    return places;
}
