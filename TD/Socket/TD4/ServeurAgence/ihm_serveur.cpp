#include "ihm_serveur.h"
#include "ui_ihm_serveur.h"

#include <QNetworkInterface>
#include <QBuffer>

IHM_Serveur::IHM_Serveur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IHM_Serveur)
{
    ui->setupUi(this);

    client = nullptr;

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
    ui->textEditEtat->append("onQTcpSocket_disconnected");
}

void IHM_Serveur::onQTcpSocket_readyRead()
{
    ui->textEditEtat->append("onQTcpSocket_readyRead");
}

void IHM_Serveur::onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError)
{
    ui->textEditEtat->append("onQTcpSocket_errorOccured");
}

void IHM_Serveur::onQTcpSocket_newConnection()
{
    if(client != nullptr)
    {
        client->close();
        delete client;
    }

    client = socketEcoute.nextPendingConnection();

    connect(client, &QTcpSocket::connected,
            this, &IHM_Serveur::onQTcpSocket_connected);
    connect(client, &QTcpSocket::disconnected,
            this, &IHM_Serveur::onQTcpSocket_disconnected);
    connect(client, &QTcpSocket::readyRead,
            this, &IHM_Serveur::onQTcpSocket_readyRead);
    connect(client, &QTcpSocket::errorOccurred,
            this, &IHM_Serveur::onQTcpSocket_errorOccured);

    QHostAddress addresseClient = client->peerAddress();
    ui->textEditEtat->append("Client : " + addresseClient.toString());
}

void IHM_Serveur::envoyerVols()
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

void IHM_Serveur::envoyerPlaces(int ref)
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
    // mise à jour des places réservées
    foreach(avion *a, lesVols)
    {
        if (a->infosVol.reference==ref)
        {
            a->siegesOccupees.append(place);
        }
    }
    // envoyer au client les places réservées pour le vol ayant la réf "ref"
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

