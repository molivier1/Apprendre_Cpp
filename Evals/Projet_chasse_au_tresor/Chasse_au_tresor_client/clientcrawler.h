/*
* File: clientcrawler.h
* Author: molivier
*
* Created on 06 decembre 2023, 13:45
* Modified on 06 decembre 2023, 16:30
* Description : Client crawler
*
*/

#ifndef CLIENTCRAWLER_H
#define CLIENTCRAWLER_H

#include <QWidget>
#include <QTcpSocket>
#include <QGridLayout>
#include <QToolButton>
#include <QBuffer>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientCrawler; }
QT_END_NAMESPACE

class ClientCrawler : public QWidget
{
    Q_OBJECT

public:
    ClientCrawler(QWidget *parent = nullptr);
    ~ClientCrawler();

private slots:
    void onQTcpSocket_connected();
    void onQTcpSocket_disconnected();
    void onQTcpSocket_readyRead();
    void onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError);

    void on_pushButtonConnexion_clicked();

    void on_pushButtonUp_clicked();

    void on_pushButtonLeft_clicked();

    void on_pushButtonRight_clicked();

    void on_pushButtonDown_clicked();

private:
    Ui::ClientCrawler *ui;

    QTcpSocket *socketClient;

    QGridLayout *grille;

    const int TAILLE = 20;
};
#endif // CLIENTCRAWLER_H
