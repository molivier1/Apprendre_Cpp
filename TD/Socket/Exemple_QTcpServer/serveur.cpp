#include "serveur.h"
#include "ui_serveur.h"

Serveur::Serveur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Serveur)
{
    ui->setupUi(this);

    connect(&sockEcoute,
            &QTcpServer::acceptError,
            this,
            &Serveur::onQTcpServer_acceptError);

    connect(&sockEcoute,
            &QTcpServer::newConnection,
            this,
            &Serveur::onQTcpServer_newConnection);

    connect(&sockEcoute,
            &QTcpServer::pendingConnectionAvailable,
            this,
            &Serveur::onQTcpServer_pendingConnectionAvailable);
}

Serveur::~Serveur()
{
    delete ui;
}


void Serveur::on_pushButtonLancerServeur_clicked()
{
    if (sockEcoute.listen(QHostAddress::Any, ui->spinBoxPort->value()))
    {
        ui->textEditLogEvents->append("Lancement du serveur sur le port : " + ui->spinBoxPort->text());
    }
    else
    {
        ui->textEditLogEvents->append("pb lancement de l'écoute sur le port : " + ui->spinBoxPort->text());
    }
}

void Serveur::onQTcpServer_acceptError(QAbstractSocket::SocketError socketError)
{
    ui->textEditLogEvents->append(sockEcoute.errorString());
}

void Serveur::onQTcpServer_newConnection()
{
    ui->textEditLogEvents->append("newConnection");
    QTcpSocket *socketDialogue = sockEcoute.nextPendingConnection();

}

void Serveur::onQTcpServer_pendingConnectionAvailable()
{
    ui->textEditLogEvents->append("pendingConnectionAvailable");
}
