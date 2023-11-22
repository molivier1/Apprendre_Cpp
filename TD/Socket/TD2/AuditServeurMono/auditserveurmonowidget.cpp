#include "auditserveurmonowidget.h"
#include "ui_auditserveurmonowidget.h"
#include <QHostInfo>
#include <QNetworkInterface>

AuditServeurMonoWidget::AuditServeurMonoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuditServeurMonoWidget)
    , socketDialogueClient(nullptr)
{
    ui->setupUi(this);

    socketEcouteServeur = new QTcpServer;

    socketDialogueClient = nullptr;

    connect(socketEcouteServeur, &QTcpServer::acceptError,
            this, &AuditServeurMonoWidget::onQTcpServer_acceptError);
    connect(socketEcouteServeur, &QTcpServer::newConnection,
            this, &AuditServeurMonoWidget::onQTcpServer_newConnection);

    connect(&process, &QProcess::readyReadStandardOutput,
            this, &AuditServeurMonoWidget::onQProcess_readyReadStandardOutput);
}


AuditServeurMonoWidget::~AuditServeurMonoWidget()
{
    if(socketDialogueClient != nullptr)
    {
        socketDialogueClient->close();
        delete socketDialogueClient;
    }
    delete socketEcouteServeur;
    delete ui;
}


void AuditServeurMonoWidget::on_pushButtonLancemenServeur_clicked()
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

void AuditServeurMonoWidget::onQTcpServer_acceptError(const QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    ui->textEditInformations->append("Serveur : " + socketEcouteServeur->errorString());
}

void AuditServeurMonoWidget::onQTcpServer_newConnection()
{
    if(socketDialogueClient != nullptr)
    {
        socketDialogueClient->close();
        delete socketDialogueClient;
    }

    socketDialogueClient = socketEcouteServeur->nextPendingConnection();

    connect(socketDialogueClient, &QTcpSocket::connected,
            this, &AuditServeurMonoWidget::onQTcpSocketConnected);
    connect(socketDialogueClient, &QTcpSocket::disconnected,
            this, &AuditServeurMonoWidget::onQTcpSocketDisconnected);
    connect(socketDialogueClient, &QTcpSocket::readyRead,
            this, &AuditServeurMonoWidget::onQTcpSocketReadyRead);
    connect(socketDialogueClient, &QTcpSocket::errorOccurred,
            this, &AuditServeurMonoWidget::onQTcpSocketErrorOccured);
    connect(socketDialogueClient, &QTcpSocket::hostFound,
            this, &AuditServeurMonoWidget::onQTcpSocketHostFound);
    connect(socketDialogueClient, &QTcpSocket::stateChanged,
            this, &AuditServeurMonoWidget::onQTcpSocketStateChanged);
    connect(socketDialogueClient, &QTcpSocket::aboutToClose,
            this, &AuditServeurMonoWidget::onQTcpSocketAboutToClose);

    QHostAddress addresseClient = socketDialogueClient->peerAddress();
    ui->textEditInformations->append("Client : " + addresseClient.toString());
}

void AuditServeurMonoWidget::onQTcpSocketConnected()
{
    ui->textEditInformations->append("Client connecté");
}

void AuditServeurMonoWidget::onQTcpSocketDisconnected()
{
    disconnect(socketDialogueClient, nullptr, this, nullptr);
    socketDialogueClient->deleteLater();
    socketDialogueClient = nullptr;
    ui->textEditInformations->append("Client détconnecté");
}

void AuditServeurMonoWidget::onQTcpSocketReadyRead()
{
    QString donneesClient;
    donneesClient = socketDialogueClient->readAll();

    QString reponse;

    if (donneesClient == "u")
    {
        reponse = getenv("USER");
        socketDialogueClient->write(reponse.toLatin1());
        ui->textEditInformations->append("Réponse au client : " + reponse);
    }

    if (donneesClient == "c")
    {
        reponse = QHostInfo::localHostName();
        socketDialogueClient->write(reponse.toLatin1());
        ui->textEditInformations->append("Réponse au client : " + reponse);
    }

    if (donneesClient == "o")
    {
        process.start("uname"); // récupération de l'OS
    }

    if (donneesClient == "a")
    {
        process.start("uname",QStringList("-p")); // récupération de l'architecture
    }
}

void AuditServeurMonoWidget::onQTcpSocketErrorOccured(const QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    ui->textEditInformations->append("Client : " + socketDialogueClient->errorString());
}

void AuditServeurMonoWidget::onQTcpSocketHostFound()
{
    ui->textEditInformations->append("host found");
}

void AuditServeurMonoWidget::onQTcpSocketStateChanged(const QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState :
        ui->textEditInformations->append("The socket is not connected.");
        break;

    case QAbstractSocket::HostLookupState :
        ui->textEditInformations->append("The socket is performing a host name lookup.");
        break;

    case QAbstractSocket::ConnectingState :
        ui->textEditInformations->append("The socket has started establishing a connection.");
        break;

    case QAbstractSocket::ConnectedState :
        ui->textEditInformations->append("A connection is established.");
        break;

    case QAbstractSocket::BoundState :
        ui->textEditInformations->append("The socket is bound to an address and port.");
        break;

    case QAbstractSocket::ClosingState :
        ui->textEditInformations->append("The socket is about to close (data may still be waiting to be written).");
        break;

    case QAbstractSocket::ListeningState :
        ui->textEditInformations->append("For internal use only.");
        break;
    }
}

void AuditServeurMonoWidget::onQTcpSocketAboutToClose()
{
    ui->textEditInformations->append("about to close");
}

void AuditServeurMonoWidget::onQTcpSocket_BytesWritten(quint64 bytes)
{
    ui->textEditInformations->append(QString::number(bytes) + " bytes written");
}

void AuditServeurMonoWidget::onQProcess_readyReadStandardOutput()
{
    QString reponse = process.readAllStandardOutput();
    if(!reponse.isEmpty())
    {
        socketDialogueClient->write(reponse.toLatin1());
        ui->textEditInformations->append("Réponse au client : " + reponse);
    }
}
