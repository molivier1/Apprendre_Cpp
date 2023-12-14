#ifndef SERVEURMULTI_H
#define SERVEURMULTI_H

#include <QWidget>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QTimer>
#include <QDateTime>
#include <QNetworkInterface>

QT_BEGIN_NAMESPACE
namespace Ui { class ServeurMulti; }
QT_END_NAMESPACE

class ServeurMulti : public QWidget
{
    Q_OBJECT

public:
    ServeurMulti(QWidget *parent = nullptr);
    ~ServeurMulti();

private:
    Ui::ServeurMulti *ui;
    QWebSocketServer *sock;
    QList <QWebSocket *> listeClient;
    QTimer *majDate;

    void onQWebSocketServer_newConnection();
    void onQWebSocket_textMessageReceived(QString string);
    void onQtimer_majDate();
};
#endif // SERVEURMULTI_H
