#ifndef SERVEURMONO_H
#define SERVEURMONO_H

#include <QWidget>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QTimer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class ServeurMono; }
QT_END_NAMESPACE

class ServeurMono : public QWidget
{
    Q_OBJECT

public:
    ServeurMono(QWidget *parent = nullptr);
    ~ServeurMono();

private:
    Ui::ServeurMono *ui;
    QWebSocketServer *sock;
    QWebSocket *client;
    QTimer *majDate;

    void onQWebSocketServer_newConnection();
    void onQWebSocket_textMessageReceived(QString string);
    void onQtimer_majDate();
};
#endif // SERVEURMONO_H
