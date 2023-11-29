#include "serveurmono.h"
#include "ui_serveurmono.h"

ServeurMono::ServeurMono(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServeurMono)
{
    ui->setupUi(this);

    sock = new QWebSocketServer();

    client = nullptr;

    connect(sock, &QWebSocketServer::newConnection, this, &ServeurMono::onQWebSocketServer_newConnection);
}

ServeurMono::~ServeurMono()
{
    delete ui;
}

void ServeurMono::onQWebSocketServer_newConnection()
{

    connect(sock, &QWebSocket::textMessageReceived, this, &ServeurMono::onQWebSocket_textMessageReceived);
}

void ServeurMono::onQWebSocket_textMessageReceived(QString string)
{

}

void ServeurMono::onQtimer_majDate()
{

}

