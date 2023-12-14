/*
* File: serveurcrawler.cpp
* Author: molivier
*
* Created on 06 decembre 2023, 13:45
* Modified on 06 decembre 2023, 16:30
* Description : Serveur multiclient crawler
*
*/

#include "serveurcrawler.h"
#include "ui_serveurcrawler.h"

ServeurCrawler::ServeurCrawler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServeurCrawler)
{
    ui->setupUi(this);

    connect(&socketEcoute, &QTcpServer::newConnection, this, &ServeurCrawler::onQTcpServer_newConnection);
}

ServeurCrawler::~ServeurCrawler()
{
    delete ui;
}

void ServeurCrawler::onQTcpServer_newConnection()
{
    // récupération de la socket de communication du client
    QTcpSocket *client=socketEcoute.nextPendingConnection();

    // connection signal/slot pour la socket
    connect(client,&QTcpSocket::disconnected,this,&ServeurCrawler::onQTcpSocket_disconnected);
    connect(client,&QTcpSocket::readyRead,this,&ServeurCrawler::onQTcpSocket_readyRead);
    connect(client,&QTcpSocket::errorOccurred,this,&ServeurCrawler::onQTcpSocket_errorOccured);
    // création et ajout du client dans la liste des clients
    listeSocketsClient.append(client);

    qDebug() << "nouvelle connexion " + client->peerAddress().toString()
                + ":" + QString::number(client->peerPort());

    QPoint positionUnique = DonnerPositionUnique();
    listePositions.append(positionUnique);
    EnvoyerDonnees(client, positionUnique, "start");
}

void ServeurCrawler::onQTcpSocket_readyRead()
{
    quint16 taille=0;
    QChar commande;

    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    int indexClient1 = listeSocketsClient.indexOf(client);
    int indexClient2;

    QPoint newPosClient1;
    QPoint newPosClient2;

    // Il y a au moins le champs taille d'arrive
    if (client->bytesAvailable() >= (qint64)sizeof(taille))
    {
        // Lecture de la taille de la trame
        QDataStream in(client);
        in >> taille;
        // Le reste de la trame est disponible
        if (client->bytesAvailable() >= (qint64)taille)
        {
            newPosClient1 = listePositions.at(indexClient1);
            // Lecture de la commande
            in>>commande;
            switch (commande.toLatin1()) {
            case 'U':
                newPosClient1.setY(newPosClient1.y()-1);
                break;

            case 'D':
                newPosClient1.setY(newPosClient1.y()+1);
                break;

            case 'L':
                newPosClient1.setX(newPosClient1.x()-1);
                break;

            case 'R':
                newPosClient1.setX(newPosClient1.x()+1);
                break;
            }
            if (newPosClient1.x()<0)
            {
                newPosClient1.setX(1);
            }

            if (newPosClient1.x()>=TAILLE)
            {
                newPosClient1.setX(TAILLE-2);
            }

            if (newPosClient1.y()<0)
            {
                newPosClient1.setY(1);
            }

            if (newPosClient1.y()>=TAILLE)
            {
                newPosClient1.setY(TAILLE-2);
            }
            //listePositions.replace(indexClient, newPos);
            if(listePositions.contains(newPosClient1))
            {
                indexClient2 = listePositions.indexOf(newPosClient1);

                newPosClient1 = DonnerPositionUnique();
                listePositions.replace(indexClient1, newPosClient1);

                newPosClient2 = DonnerPositionUnique();
                listePositions.replace(indexClient2, newPosClient2);

                EnvoyerDonnees(listeSocketsClient.at(indexClient1), newPosClient1, "collision");

                EnvoyerDonnees(listeSocketsClient.at(indexClient2), newPosClient2, "collision");
            } else {
                if (tresor == newPosClient1)
                {
                    foreach(QTcpSocket *clientCourant, listeSocketsClient)
                    {
                        QPoint win;
                        win.setX(-1);
                        win.setY(-1);
                        EnvoyerDonnees(clientCourant, win, "Victoire de " + client->peerAddress().toString());
                        clientCourant->disconnectFromHost();
                    }

                    tresor = DonnerPositionUnique();
                }
                else
                {
                    listePositions.replace(indexClient1, newPosClient1);
                    EnvoyerDonnees(client, newPosClient1, "vide");
                }
            }
        }
    }
}

void ServeurCrawler::onQTcpSocket_disconnected()
{
    // récupérer la socket du client se déconnectant
    QTcpSocket *client=qobject_cast<QTcpSocket *>(sender());
    // récupérer l'index de ce client dans la liste
    int index= listeSocketsClient.indexOf(client);
    // supprimer le client de la liste
    if (index!=-1)
    {
        listeSocketsClient.removeAt(index);
        listePositions.removeAt(index);
    }
    // afficher un message avec l'ip et le port du client deconnecté
    qDebug() << "Le client " + client->peerAddress().toString() + ":" +
                QString::number(client->peerPort()) + " s'est déconnecté";
}

void ServeurCrawler::onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError)
{
    qDebug() << "errorOccured";
}

void ServeurCrawler::EnvoyerDonnees(QTcpSocket *client, QPoint pt, QString msg)
{
    quint16 taille=0;
    QBuffer tampon;
    double distance = CalculerDistance(pt);
    // construction de la trame à envoyer au client
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<pt<<msg<<distance;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    client->write(tampon.buffer());
}

void ServeurCrawler::afficherGrille()
{

}

void ServeurCrawler::viderGrille()
{

}

QPoint ServeurCrawler::DonnerPositionUnique()
{
    QRandomGenerator gen;
    QPoint pt;
    gen.seed(QDateTime::currentMSecsSinceEpoch());
    int ligne;
    int colonne;
    do
    {
        ligne = gen.bounded(TAILLE);
        QThread::usleep(20000);	// attendre 20ms
        colonne = gen.bounded(TAILLE);
        QThread::usleep(20000);	// attendre 20ms
        pt = QPoint(colonne,ligne);
    }while (listePositions.contains(pt));
    return pt;
}

double ServeurCrawler::CalculerDistance(QPoint pos)
{
    double distance;
    int xVecteur = tresor.x()-pos.x();
    int yVecteur = tresor.y()-pos.y();
    distance = sqrt((xVecteur*xVecteur + yVecteur*yVecteur));
    return distance;
}


void ServeurCrawler::on_pushButtonLancementServeur_clicked()
{
    if(!socketEcoute.listen(QHostAddress::Any,ui->spinBoxPort->value()))
    {
        QString message = "Impossible de démarrer le serveur " + socketEcoute.errorString();
        qDebug() << message;
    }
    else
    {
        QList<QHostAddress> listeAdresses = QNetworkInterface::allAddresses();
        QList<QHostAddress>::iterator it;
        for(it = listeAdresses.begin(); it != listeAdresses.end();it++)
        {
            if(it->toIPv4Address())
                qDebug() << "Adresse serveur : " + it->toString();
        }
        qDebug() << "N° du port : " + QString::number(socketEcoute.serverPort());
    }
}
