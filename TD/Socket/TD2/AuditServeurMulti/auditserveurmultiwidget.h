#ifndef AUDITSERVEURMULTIWIDGET_H
#define AUDITSERVEURMULTIWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class AuditServeurMultiWidget; }
QT_END_NAMESPACE

class AuditServeurMultiWidget : public QWidget
{
    Q_OBJECT

public:
    AuditServeurMultiWidget(QWidget *parent = nullptr);
    ~AuditServeurMultiWidget();
    void onQTcpServer_acceptError(const QAbstractSocket::SocketError socketError);
    void onQTcpServer_newConnection();

    void onQTcpSocket_BytesWritten(quint64 bytes);
    void onQProcess_readyReadStandardOutput();

private slots:
    void on_pushButtonLancemenServeur_clicked();

private:
    Ui::AuditServeurMultiWidget *ui;

    QList <QTcpSocket *> listeSocketsDialogueClient;
    QTcpServer *socketEcouteServeur;
    QList <QProcess *> listeProcess;

    void onQTcpSocketConnected();
    void onQTcpSocketDisconnected();
    void onQTcpSocketReadyRead();
    void onQTcpSocketErrorOccured(const QAbstractSocket::SocketError socketError);
    void onQTcpSocketHostFound();
    void onQTcpSocketStateChanged(const QAbstractSocket::SocketState socketState);
    void onQTcpSocketAboutToClose();

};
#endif // AUDITSERVEURMULTIWIDGET_H
