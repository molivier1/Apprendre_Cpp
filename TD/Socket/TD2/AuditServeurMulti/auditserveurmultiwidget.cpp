#include "auditserveurmultiwidget.h"
#include "ui_auditserveurmultiwidget.h"
#include <QNetworkInterface>

AuditServeurMultiWidget::AuditServeurMultiWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuditServeurMultiWidget)
{
    ui->setupUi(this);

    socketEcouteServeur = new QTcpServer;

    socketEcouteServeur->setMaxPendingConnections(30);

    connect(socketEcouteServeur, &QTcpServer::acceptError,
            this, &AuditServeurMultiWidget::onQTcpServer_acceptError);
    connect(socketEcouteServeur, &QTcpServer::newConnection,
            this, &AuditServeurMultiWidget::onQTcpServer_newConnection);
}

AuditServeurMultiWidget::~AuditServeurMultiWidget()
{
    delete socketEcouteServeur;
    delete ui;
}

void AuditServeurMultiWidget::on_pushButtonLancemenServeur_clicked()
{
    if(!socketEcouteServeur->listen(QHostAddress::Any,ui->spinBoxPort->value()))
    {
        QString message = "Impossible de démarrer le serveur " + socketEcouteServeur->errorString();
        ui->textEditInformations->append(message);
    }
    else
    {
        QList<QHostAddress> listeAdresses = QNetworkInterface::allAddresses();
        QList<QHostAddress>::iterator it;
        for(it = listeAdresses.begin(); it != listeAdresses.end();it++)
        {
            if(it->toIPv4Address())
                ui->textEditInformations->append("Adresse serveur : " + it->toString());
        }
        ui->textEditInformations->append("N° du port : " + QString::number(socketEcouteServeur->serverPort()));
        ui->pushButtonLancemenServeur->setEnabled(false);
        ui->spinBoxPort->setEnabled(false);
    }
}

void AuditServeurMultiWidget::onQTcpServer_acceptError(const QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    ui->textEditInformations->append("Serveur : " + socketEcouteServeur->errorString());
}

void AuditServeurMultiWidget::onQTcpServer_newConnection()
{
    if(socketDialogueClient != nullptr)
    {
        socketDialogueClient->close();
        delete socketDialogueClient;
    }

    socketDialogueClient = socketEcouteServeur->nextPendingConnection();

    connect(socketDialogueClient, &QTcpSocket::connected,
            this, &AuditServeurMultiWidget::onQTcpSocketConnected);
    connect(socketDialogueClient, &QTcpSocket::disconnected,
            this, &AuditServeurMultiWidget::onQTcpSocketDisconnected);
    connect(socketDialogueClient, &QTcpSocket::readyRead,
            this, &AuditServeurMultiWidget::onQTcpSocketReadyRead);
    connect(socketDialogueClient, &QTcpSocket::errorOccurred,
            this, &AuditServeurMultiWidget::onQTcpSocketErrorOccured);
    connect(socketDialogueClient, &QTcpSocket::hostFound,
            this, &AuditServeurMultiWidget::onQTcpSocketHostFound);
    connect(socketDialogueClient, &QTcpSocket::stateChanged,
            this, &AuditServeurMultiWidget::onQTcpSocketStateChanged);
    connect(socketDialogueClient, &QTcpSocket::aboutToClose,
            this, &AuditServeurMultiWidget::onQTcpSocketAboutToClose);

    QHostAddress addresseClient = socketDialogueClient->peerAddress();
    ui->textEditInformations->append("Client : " + addresseClient.toString());
}

