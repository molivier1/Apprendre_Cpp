#include "interfaceserveurtchat.h"
#include "ui_interfaceserveurtchat.h"

InterfaceServeurTchat::InterfaceServeurTchat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InterfaceServeurTchat)
{
    ui->setupUi(this);

    ui->lineEditPort->setText("3456");

    socketServeur = new QWebSocketServer("", QWebSocketServer::NonSecureMode, this);
}

InterfaceServeurTchat::~InterfaceServeurTchat()
{
    foreach(QWebSocket *clientCourant, listeClients)
    {
        clientCourant->close();
        delete clientCourant;
    }

    delete ui;
}

void InterfaceServeurTchat::broadcastMessage(QString msg)
{
    foreach (QWebSocket *c, listeClients) {
        c->sendTextMessage(msg);
    }
}

void InterfaceServeurTchat::onQWebSocketServer_newConnection()
{
    QWebSocket *newClient = socketServeur->nextPendingConnection();

    connect(newClient, &QWebSocket::textMessageReceived, this, &InterfaceServeurTchat::onQWebSocket_textMessageReceived);

    QHostAddress addresseClient = newClient->peerAddress();
    ui->textEditLogs->append("Client : " + addresseClient.toString());
    listeClients.append(newClient);
}

void InterfaceServeurTchat::onQWebSocket_textMessageReceived(const QString &message)
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());

    ui->textEditLogs->append(client->peerAddress().toString() + " : " + message);

    broadcastMessage(message);
}

void InterfaceServeurTchat::onQWebSocket_disconnected()
{
    // récupérer la socket du client se déconnectant
    QTcpSocket *client=qobject_cast<QTcpSocket *>(sender());
    // afficher un message avec l'ip et le port du client deconnecté
    ui->textEditLogs->append("Le client " + client->peerAddress().toString() + ":" +
                             QString::number(client->peerPort()) + " s'est déconnecté");
}

void InterfaceServeurTchat::on_pushButtonLancer_clicked()
{
    int portNumber = 3456;

    if (!ui->lineEditPort->text().isEmpty())
    {
        portNumber = ui->lineEditPort->text().toInt();
    }

    if(!socketServeur->listen(QHostAddress::Any, portNumber))
    {
        QString message = "Impossible de démarrer le serveur " + socketServeur->errorString();
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
        ui->textEditLogs->append("N° du port : " + QString::number(socketServeur->serverPort()));
    }

    connect(socketServeur, &QWebSocketServer::newConnection, this, &InterfaceServeurTchat::onQWebSocketServer_newConnection);

    ui->pushButtonLancer->setDisabled(true);
}
