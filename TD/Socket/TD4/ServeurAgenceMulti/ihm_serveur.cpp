#include "ihm_serveur.h"
#include "ui_ihm_serveur.h"

#include <QNetworkInterface>
#include <QBuffer>

IHM_Serveur::IHM_Serveur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IHM_Serveur)
{
    ui->setupUi(this);

    genererListeVols();

    connect(&socketEcoute, &QTcpServer::newConnection,
            this, &IHM_Serveur::onQTcpSocket_newConnection);
}

IHM_Serveur::~IHM_Serveur()
{
    delete ui;
}

void IHM_Serveur::onQTcpSocket_connected()
{
    ui->textEditEtat->append("onQTcpSocket_connected");
}

void IHM_Serveur::onQTcpSocket_disconnected()
{
    // récupérer la socket du client se déconnectant
    QTcpSocket *client=qobject_cast<QTcpSocket *>(sender());
    // récupérer l'index de ce client dans la liste
    int index= getIndexClient(client);
    // supprimer le client de la liste
    if (index!=-1)
    {
        listeClients.removeAt(index);
    }
    // afficher un message avec l'ip et le port du client deconnecté
    ui->textEditEtat->append("Le client " + client->peerAddress().toString() + ":" +
                             QString::number(client->peerPort()) + " s'est déconnecté");
}

void IHM_Serveur::onQTcpSocket_readyRead()
{
    quint16 taille=0;
    QChar commande;
    int refVol;
    int nroPlace;
    QString nom;
    QString prenom;
    QString email;
    int indexClient;

    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    // Il y a au moins le champs taille d'arrive
    if (client->bytesAvailable() >= (qint64)sizeof(taille))
    {
        // Lecture de la taille de la trame
        QDataStream in(client);
        in >> taille;
        // Le reste de la trame est disponible
        if (client->bytesAvailable() >= (qint64)taille)
        {
            // Lecture de la commande
            in>>commande;
            switch (commande.toLatin1()) {
            case 'P':
                // Lecture de la référence du vol
                in >> refVol;

                ui->textEditEtat->append("Réception choix d'un vol : " + QString::number(refVol));

                envoyerPlaces(client, refVol);
                break;

            case 'R':
                // Lecture de la validation
                in>>refVol;
                in>>nroPlace;
                in>>nom;
                in>>prenom;
                in>>email;

                ui->textEditEtat->append("Réception validation : " + QString::number(refVol) + " " +
                                         QString::number(nroPlace) + " " +
                                         nom + " " + prenom + " " + email);

                indexClient = getIndexClient(client);

                listeClients.at(indexClient)->setReferenceVol(refVol);
                listeClients.at(indexClient)->setNumeroPlace(nroPlace);
                listeClients.at(indexClient)->setNom(nom);
                listeClients.at(indexClient)->setPrenom(prenom);
                listeClients.at(indexClient)->setEmail(email);

                ajouterReservation(refVol, nroPlace, nom, prenom, email);
                break;
            }
        }
    }
}

void IHM_Serveur::onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError)
{
    ui->textEditEtat->append("onQTcpSocket_errorOccured");
}

void IHM_Serveur::onQTcpSocket_newConnection()
{
    // récupération de la socket de communication du client
    QTcpSocket *client=socketEcoute.nextPendingConnection();

    // connection signal/slot pour la socket
    connect(client,&QTcpSocket::connected,this,&IHM_Serveur::onQTcpSocket_connected);
    connect(client,&QTcpSocket::disconnected,this,&IHM_Serveur::onQTcpSocket_disconnected);
    connect(client,&QTcpSocket::readyRead,this,&IHM_Serveur::onQTcpSocket_readyRead);
    connect(client,&QTcpSocket::errorOccurred,this,&IHM_Serveur::onQTcpSocket_errorOccured);
    // création et ajout du client dans la liste des clients
    Client *nouveauClient=new Client();
    nouveauClient->setSockClient(client);
    nouveauClient->setReferenceVol(lesVols.at(0)->infosVol.reference);
    listeClients.append(nouveauClient);
    // envoyer la listes des vols au client entrant
    envoyerVols(client);
    ui->textEditEtat->append("nouvelle connexion " + nouveauClient->getSockClient()->peerAddress().toString()
                             + ":" + QString::number(nouveauClient->getSockClient()->peerPort()));
}

int IHM_Serveur::getIndexClient(QTcpSocket *client)
{
    int cmp = 0;
    foreach(Client *clientCourant, listeClients)
    {
        if (clientCourant->getSockClient() == client)
        {
            return cmp;
        }
        cmp ++;
    }

    return -1;
}

void IHM_Serveur::envoyerVols(QTcpSocket *client)
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('V');
    // generation de la liste des vols
    QList <vol> vols;
    foreach(avion *a, lesVols)
    {
        vols<<a->infosVol;
    }
    // construction de la trame à envoyer au client

    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<vols;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    client->write(tampon.buffer());
}

void IHM_Serveur::envoyerPlaces(QTcpSocket *client, int ref)
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('P');
    // generation de la liste des vols
    QList <int> places;
    foreach(avion *a, lesVols)
    {
        if (a->infosVol.reference==ref)
        {
            places=a->siegesOccupees;
        }
    }
    // construction de la trame à envoyer au client

    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<places;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    client->write(tampon.buffer());
}

void IHM_Serveur::ajouterReservation(int ref, int place, QString nom, QString prenom, QString email)
{
    // mise a jour des places occupees pour le vol ref
    foreach(avion *a, lesVols)
    {
        if (a->infosVol.reference==ref)
        {
            a->siegesOccupees.append(place);
        }
    }
    // envoyer les places occupees à tous les clients reservant pour le vol
    // ayant la réference "ref"
    foreach (Client *client, listeClients) {
        if (client->getReferenceVol()==ref)
        {
            envoyerPlaces(client->getSockClient(),ref);
        }
    }
}

void IHM_Serveur::genererListeVols()
{
    avion *v1=new avion;
    v1->infosVol.reference=1234;
    v1->infosVol.denomination="Paris - Londre";
    v1->siegesOccupees<<1<<2<<4<<5<<12;

    avion *v2=new avion;
    v2->infosVol.reference=2345;
    v2->infosVol.denomination="Paris - New York";
    v2->siegesOccupees<<10<<12<<14;

    avion *v3=new avion;
    v3->infosVol.reference=3456;
    v3->infosVol.denomination="Paris - Sydney";
    v3->siegesOccupees<<1<<3<<8<<13<<15;

    lesVols.append(v1);
    lesVols.append(v2);
    lesVols.append(v3);
}


void IHM_Serveur::on_pushButtonLancerServeur_clicked()
{
    if(!socketEcoute.listen(QHostAddress::Any,ui->spinBoxPort->value()))
    {
        QString message = "Impossible de démarrer le serveur " + socketEcoute.errorString();
        ui->textEditEtat->append(message);
    }
    else
    {
        QList<QHostAddress> listeAdresses = QNetworkInterface::allAddresses();
        QList<QHostAddress>::iterator it;
        for(it = listeAdresses.begin(); it != listeAdresses.end();it++)
        {
            if(it->toIPv4Address())
                ui->textEditEtat->append("Adresse serveur : " + it->toString());
        }
        ui->textEditEtat->append("N° du port : " + QString::number(socketEcoute.serverPort()));
        ui->pushButtonLancerServeur->setEnabled(false);
        ui->spinBoxPort->setEnabled(false);
    }
}

