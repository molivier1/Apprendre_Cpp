#include "serveurmulti.h"
#include "ui_serveurmulti.h"

ServeurMulti::ServeurMulti(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServeurMulti)
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

    connect(sock, &QWebSocketServer::newConnection, this, &ServeurMulti::onQWebSocketServer_newConnection);

    majDate = new QTimer(this);
    connect(majDate, &QTimer::timeout, this, &ServeurMulti::onQtimer_majDate);
}

ServeurMulti::~ServeurMulti()
{
    if(client != nullptr)
    {
        client->close();
        delete client;
    }
    delete sock;
    delete ui;
}

void ServeurMulti::onQWebSocketServer_newConnection()
{
    if(client != nullptr)
    {
        client->close();
        delete client;
    }

    client = sock->nextPendingConnection();

    connect(client, &QWebSocket::textMessageReceived, this, &ServeurMulti::onQWebSocket_textMessageReceived);

    QHostAddress addresseClient = client->peerAddress();
    ui->textEditLogs->append("Client : " + addresseClient.toString());
}

void ServeurMulti::onQWebSocket_textMessageReceived(QString string)
{
    ui->textEditLogs->append(client->peerAddress().toString() + " : " + string);

    if(string == "date")
    {
        majDate->start(2000);
    }
}

void ServeurMulti::onQtimer_majDate()
{
    if (client->isValid())
    {
        ui->textEditLogs->append("Envoie : " + QDateTime::currentDateTime().toString());
        client->sendTextMessage(QDateTime::currentDateTime().toString());
    }
}
