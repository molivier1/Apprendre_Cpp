#include "auditserveurmultiwidget.h"
#include "ui_auditserveurmultiwidget.h"
#include <QHostInfo>
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
    QTcpSocket *socketDialogueClient = qobject_cast<QTcpSocket * >(sender());
    if(socketDialogueClient != nullptr)
    {
        socketDialogueClient->close();
        delete socketDialogueClient;
    }
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
    QProcess *process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput,
            this, &AuditServeurMultiWidget::onQProcess_readyReadStandardOutput);
    listeProcess.append(process);

    QTcpSocket *socketDialogueClient = socketEcouteServeur->nextPendingConnection();

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
    // complétez pour les autres signaux

    listeSocketsDialogueClient.append(socketDialogueClient);  // ajout dans la liste des sockets

    QHostAddress addresseClient = socketDialogueClient->peerAddress();
    ui->textEditInformations->append("Client : " + addresseClient.toString());
}

void AuditServeurMultiWidget::onQTcpSocketConnected()
{
    ui->textEditInformations->append("Client connecté");
}

void AuditServeurMultiWidget::onQTcpSocketDisconnected()
{
    QTcpSocket *socketDialogueClient = qobject_cast<QTcpSocket * >(sender());
    disconnect(socketDialogueClient, nullptr, this, nullptr);
    socketDialogueClient->deleteLater();
    socketDialogueClient = nullptr;
    ui->textEditInformations->append("Client détconnecté");
}

void AuditServeurMultiWidget::onQTcpSocketReadyRead()
{
    QTcpSocket *socketDialogueClient = qobject_cast<QTcpSocket * >(sender());
    int indexClient = listeSocketsDialogueClient.indexOf(socketDialogueClient);
    QChar commande;
    QString reponse;
    if (socketDialogueClient->bytesAvailable()) {
        QByteArray tampon = socketDialogueClient->readAll();
        commande = tampon.at(0);
        QString message = "Commande reçu de " + socketDialogueClient->peerAddress().toString() + " : ";
        message += commande;
        ui->textEditInformations->append(message);
        switch (commande.toLatin1())
        {
            case 'a' :
            listeProcess.at(indexClient)->start("uname", QStringList("-p"));
            break;

        case 'u' :
            reponse = getenv("USER");
            socketDialogueClient->write(reponse.toLatin1());
            break;

        case 'c' :
            reponse = QHostInfo::localHostName();
            socketDialogueClient->write(reponse.toLatin1());
            break;

        case 'o' :
            listeProcess.at(indexClient)->start("uname");
            break;
        }
    }
}

void AuditServeurMultiWidget::onQTcpSocketErrorOccured(const QAbstractSocket::SocketError socketError)
{
    QTcpSocket *socketDialogueClient = qobject_cast<QTcpSocket * >(sender());
    Q_UNUSED(socketError);
    ui->textEditInformations->append("Client : " + socketDialogueClient->errorString());
}

void AuditServeurMultiWidget::onQTcpSocketHostFound()
{
    ui->textEditInformations->append("host found");
}

void AuditServeurMultiWidget::onQTcpSocketStateChanged(const QAbstractSocket::SocketState socketState)
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

void AuditServeurMultiWidget::onQTcpSocketAboutToClose()
{
    ui->textEditInformations->append("about to close");
}

void AuditServeurMultiWidget::onQTcpSocket_BytesWritten(quint64 bytes)
{
    ui->textEditInformations->append(QString::number(bytes) + " bytes written");
}

void AuditServeurMultiWidget::onQProcess_readyReadStandardOutput()
{
    QProcess *process = qobject_cast<QProcess *>(sender());
    int indexProcess = listeProcess.indexOf(process);
    QString reponse = process->readAllStandardOutput();
    if(!reponse.isEmpty())
    {
        listeSocketsDialogueClient.at(indexProcess)->write(reponse.toLatin1());
        ui->textEditInformations->append("Réponse au client : " + reponse);
    }
}

