#ifndef AUDITCLIENTWIDGET_H
#define AUDITCLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class AuditClientWidget; }
QT_END_NAMESPACE

class AuditClientWidget : public QWidget
{
    Q_OBJECT

public:
    AuditClientWidget(QWidget *parent = nullptr);
    ~AuditClientWidget();

private slots:
    void on_pushButtonConnexion_clicked();

    void on_pushButtonOrdinateur_clicked();

    void on_pushButtonUtilisateur_clicked();

    void on_pushButtonArchitecture_clicked();

    void on_pushButtonOs_clicked();

private:
    Ui::AuditClientWidget *ui;
    QTcpSocket *socketDeDialogueAvecServeur;
    QString typeDeDemande;

    void onQTcpSocketConnected();
    void onQTcpSocketDisconnected();
    void onQTcpSocketReadyRead();
    void onQTcpSocketErrorOccured(const QAbstractSocket::SocketError socketError);
    void onQTcpSocketHostFound();
    void onQTcpSocketStateChanged(const QAbstractSocket::SocketState socketState);
    void onQTcpSocketAboutToClose();
    void onQTcpSocketBytesWritten(const quint64 bytes);
    void onQTcpSocketChannelBytesWritten(const int channel, const quint64 bytes);
    void onQTcpSocketChannelReadyRead(const int channel);
    void onQTcpSocketReadChannelFinished();
    void onQTcpSocketDestroyed(const QObject *obj);
};
#endif // AUDITCLIENTWIDGET_H
