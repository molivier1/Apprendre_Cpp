/*
* File: clientcrawler.cpp
* Author: molivier
*
* Created on 06 decembre 2023, 13:45
* Modified on 06 decembre 2023, 16:30
* Description : Client crawler
*
*/

#include "clientcrawler.h"
#include "ui_clientcrawler.h"

ClientCrawler::ClientCrawler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientCrawler)
{
    ui->setupUi(this);

    grille = new QGridLayout(this);

    for(int ligne=0; ligne<TAILLE; ligne++)
    {
        for (int colonne=0; colonne<TAILLE; colonne++)
        {
            QToolButton *b=new QToolButton();
            grille->addWidget(b,ligne,colonne,1,1);
        }
    }
    // Placement sur la grille des objets présents sur ui
    // les labels
    grille->addWidget(ui->labelAdresseServeur,TAILLE,0,1,5);
    grille->addWidget(ui->labelNumeroPort,TAILLE,6,1,5);
    grille->addWidget(ui->labelDistance,TAILLE+3,0,1,5);
    grille->addWidget(ui->labelInformations,TAILLE+3,12,1,5);
    // les QLineEdit adresse et port
    grille->addWidget(ui->lineEditAdresseServeur,TAILLE+1,0,1,5);
    grille->addWidget(ui->spinBoxPortServeur,TAILLE+1,6,1,5);
    // les QPushButton connexion et quitter
    grille->addWidget(ui->pushButtonConnexion,TAILLE+2,0,1,5);
    grille->addWidget(ui->pushButtonQuitter,TAILLE+2,6,1,5);
    // les QPushButton fleches
    grille->addWidget(ui->pushButtonUp,TAILLE,15,1,1);
    grille->addWidget(ui->pushButtonLeft,TAILLE+1,14,1,1);
    grille->addWidget(ui->pushButtonRight,TAILLE+1,16,1,1);
    grille->addWidget(ui->pushButtonDown,TAILLE+2,15,1,1);
    //distance et informations
    grille->addWidget(ui->lcdNumberDistance,TAILLE+3,6,1,5);
    this->setLayout(grille);

    socketClient = new QTcpSocket(this);

    connect(socketClient, &QTcpSocket::connected, this, &ClientCrawler::onQTcpSocket_connected);
    connect(socketClient, &QTcpSocket::disconnected, this, &ClientCrawler::onQTcpSocket_disconnected);
    connect(socketClient, &QTcpSocket::readyRead, this, &ClientCrawler::onQTcpSocket_readyRead);
    connect(socketClient, &QTcpSocket::errorOccurred, this, &ClientCrawler::onQTcpSocket_errorOccured);

    ui->lineEditAdresseServeur->setText("127.0.0.1");

    ui->pushButtonUp->setDisabled(true);
    ui->pushButtonDown->setDisabled(true);
    ui->pushButtonLeft->setDisabled(true);
    ui->pushButtonRight->setDisabled(true);
}

ClientCrawler::~ClientCrawler()
{
    delete ui;
}

void ClientCrawler::onQTcpSocket_connected()
{
    qDebug() << "Connecté au serveur : " + socketClient->peerAddress().toString() + ":"
                + QString::number(socketClient->peerPort());
    ui->pushButtonConnexion->setText("Déconnexion");
    ui->pushButtonUp->setDisabled(false);
    ui->pushButtonDown->setDisabled(false);
    ui->pushButtonLeft->setDisabled(false);
    ui->pushButtonRight->setDisabled(false);
}

void ClientCrawler::onQTcpSocket_disconnected()
{
    qDebug() << "Déconnecté du serveur : " + socketClient->peerAddress().toString() + ":"
                + QString::number(socketClient->peerPort());
    ui->pushButtonConnexion->setText("Connexion");
    ui->pushButtonUp->setDisabled(true);
    ui->pushButtonDown->setDisabled(true);
    ui->pushButtonLeft->setDisabled(true);
    ui->pushButtonRight->setDisabled(true);
}

void ClientCrawler::onQTcpSocket_readyRead()
{
    quint16 taille=0;
    QPoint coords;
    QString message;
    double distance;
    // Il y a au moins le champs taille d'arrive
    if (socketClient->bytesAvailable() >= (qint64)sizeof(taille))
    {
        // Lecture de la taille de la trame
        QDataStream in(socketClient);
        in >> taille;
        // Le reste de la trame est disponible
        if (socketClient->bytesAvailable() >= (qint64)taille)
        {
            // Lecture de la commande
            in>>coords;
            in>>message;
            in>>distance;

            qDebug() << "Message reçu : " << taille << coords << message << distance;
            if(coords.y()>0 && coords.x()>0)
            {
                grille->itemAtPosition(coords.y(), coords.x())->widget()->setStyleSheet("background-color : black");
            }
            ui->labelInformations->setText(message);
            ui->lcdNumberDistance->display(distance);
        }
    }
}

void ClientCrawler::onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError)
{
    qDebug() << "errorOccured";
}


void ClientCrawler::on_pushButtonConnexion_clicked()
{
    if (ui->pushButtonConnexion->text() == "Connexion")
    {
        socketClient->connectToHost(ui->lineEditAdresseServeur->text(), ui->spinBoxPortServeur->value());
    }
    else
    {
        socketClient->disconnectFromHost();
    }
}


void ClientCrawler::on_pushButtonUp_clicked()
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('U');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    socketClient->write(tampon.buffer());
}


void ClientCrawler::on_pushButtonLeft_clicked()
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('L');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    socketClient->write(tampon.buffer());
}


void ClientCrawler::on_pushButtonRight_clicked()
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('R');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    socketClient->write(tampon.buffer());
}


void ClientCrawler::on_pushButtonDown_clicked()
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('D');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    socketClient->write(tampon.buffer());
}

