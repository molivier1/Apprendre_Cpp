#include "serveurmono.h"
#include "ui_serveurmono.h"

ServeurMono::ServeurMono(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServeurMono)
{
    ui->setupUi(this);

    sock = new QWebSocketServer("", QWebSocketServer::NonSecureMode, this);

    if(!sock->listen(QHostAddress::Any, 5555))
    {
        QString message = "Impossible de démarrer le serveur " + sock->errorString();
        ui->textEditLogs->append(message);
    }
    else
    {
        QList<QHostAddress> listeAdresses = QNetworkInterface::allAddresses();
        QList<QHostAddress>::iterator it;
        for(it = listeAdresses.begin(); it != listeAdresses.end();it++)
        {
            if(it->toIPv4Address())
                ui->textEditLogs->append("Adresse serveur : " + it->toString());
        }
        ui->textEditLogs->append("N° du port : " + QString::number(sock->serverPort()));
    }

    client = nullptr;

    connect(sock, &QWebSocketServer::newConnection, this, &ServeurMono::onQWebSocketServer_newConnection);

    majDate = new QTimer(this);
    connect(majDate, &QTimer::timeout, this, &ServeurMono::onQtimer_majDate);
}

ServeurMono::~ServeurMono()
{
    if(client != nullptr)
    {
        client->close();
        delete client;
    }
    delete sock;
    delete ui;
}

void ServeurMono::onQWebSocketServer_newConnection()
{
    if(client != nullptr)
    {
        client->close();
        delete client;
    }

    client = sock->nextPendingConnection();

    connect(client, &QWebSocket::textMessageReceived, this, &ServeurMono::onQWebSocket_textMessageReceived);

    QHostAddress addresseClient = client->peerAddress();
    ui->textEditLogs->append("Client : " + addresseClient.toString());
}

void ServeurMono::onQWebSocket_textMessageReceived(QString string)
{
    ui->textEditLogs->append(client->peerAddress().toString() + " : " + string);

    if(string == "date")
    {
        majDate->start(2000);
    }
}

void ServeurMono::onQtimer_majDate()
{
    if (client->isValid())
    {
        ui->textEditLogs->append("Envoie : " + QDateTime::currentDateTime().toString());
        client->sendTextMessage(QDateTime::currentDateTime().toString());
    }
}
