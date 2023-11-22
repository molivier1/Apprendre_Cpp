#ifndef AUDITSERVEURMONOWIDGET_H
#define AUDITSERVEURMONOWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class AuditServeurMonoWidget; }
QT_END_NAMESPACE

class AuditServeurMonoWidget : public QWidget
{
    Q_OBJECT

public:
    AuditServeurMonoWidget(QWidget *parent = nullptr);
    ~AuditServeurMonoWidget();
    void onQTcpServer_acceptError(const QAbstractSocket::SocketError socketError);
    void onQTcpServer_newConnection();

    void onQTcpSocket_BytesWritten(quint64 bytes);
    void onQProcess_readyReadStandardOutput();

private slots:
    void on_pushButtonLancemenServeur_clicked();

private:
    Ui::AuditServeurMonoWidget *ui;

    QTcpSocket *socketDialogueClient;
    QTcpServer *socketEcouteServeur;
    QProcess process;

    void onQTcpSocketConnected();
    void onQTcpSocketDisconnected();
    void onQTcpSocketReadyRead();
    void onQTcpSocketErrorOccured(const QAbstractSocket::SocketError socketError);
    void onQTcpSocketHostFound();
    void onQTcpSocketStateChanged(const QAbstractSocket::SocketState socketState);
    void onQTcpSocketAboutToClose();

};
#endif // AUDITSERVEURMONOWIDGET_H
