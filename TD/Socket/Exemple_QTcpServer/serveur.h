#ifndef SERVEUR_H
#define SERVEUR_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Serveur; }
QT_END_NAMESPACE

class Serveur : public QWidget
{
    Q_OBJECT

public:
    Serveur(QWidget *parent = nullptr);
    ~Serveur();

private slots:
    void on_pushButtonLancerServeur_clicked();

    void onQTcpServer_acceptError(QAbstractSocket::SocketError socketError);
    void onQTcpServer_newConnection();
    void onQTcpServer_pendingConnectionAvailable();

    void onQtcpSocket_readyRead();

private:
    Ui::Serveur *ui;
    QTcpServer sockEcoute;
    QTcpSocket *socketDialogue;

};
#endif // SERVEUR_H
