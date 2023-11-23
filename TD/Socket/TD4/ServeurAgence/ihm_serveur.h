#ifndef IHM_SERVEUR_H
#define IHM_SERVEUR_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class IHM_Serveur; }
QT_END_NAMESPACE

class IHM_Serveur : public QWidget
{
    Q_OBJECT

public:
    IHM_Serveur(QWidget *parent = nullptr);
    ~IHM_Serveur();

private:
    Ui::IHM_Serveur *ui;
};
#endif // IHM_SERVEUR_H
