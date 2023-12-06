/*
* File: serveurcrawler.h
* Author: molivier
*
* Created on 06 decembre 2023, 13:45
* Modified on 06 decembre 2023, 16:30
* Description : Serveur multiclient crawler
*
*/

#ifndef SERVEURCRAWLER_H
#define SERVEURCRAWLER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QGridLayout>

#include <QNetworkInterface>

#include <QRandomGenerator>
#include <QDateTime>
#include <QThread>

#include <QBuffer>

QT_BEGIN_NAMESPACE
namespace Ui { class ServeurCrawler; }
QT_END_NAMESPACE

class ServeurCrawler : public QWidget
{
    Q_OBJECT

public:
    ServeurCrawler(QWidget *parent = nullptr);
    ~ServeurCrawler();

private slots:
    void onQTcpServer_newConnection();
    void onQTcpSocket_readyRead();
    void onQTcpSocket_disconnected();
    void onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError);

    void on_pushButtonLancementServeur_clicked();

private:
    Ui::ServeurCrawler *ui;

    QTcpServer socketEcoute;
    QList <QTcpSocket *> listeSocketsClient;

    QList <QPoint> listePositions;
    QPoint tresor;
    QGridLayout *grille;

    const int TAILLE = 20;

    void EnvoyerDonnees(QTcpSocket * client, QPoint pt, QString msg);
    void afficherGrille();
    void viderGrille();

    QPoint DonnerPositionUnique();
    double CalculerDistance(QPoint pos);
};
#endif // SERVEURCRAWLER_H
