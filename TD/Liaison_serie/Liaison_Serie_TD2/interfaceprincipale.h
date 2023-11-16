#ifndef INTERFACEPRINCIPALE_H
#define INTERFACEPRINCIPALE_H

#include <QMainWindow>
#include <QSerialPort>
#include "dialogconfigurerliaisongps.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class InterfacePrincipale; }
QT_END_NAMESPACE

class InterfacePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    InterfacePrincipale(QWidget *parent = nullptr);
    ~InterfacePrincipale();
    void onQSerialPort_ReadyRead();
    void DecodageNMEA(const QString &_trameNMEA);

private slots:
    void on_actionConfigurer_triggered();

    void on_actionEnregistrer_triggered();

    void on_actionOuvrir_triggered();

    void on_actionA_propos_de_triggered();

private:
    Ui::InterfacePrincipale *ui;
    QSerialPort lePort;
    DialogConfigurerLiaisonGPS configGPS;
    QLabel labelEtatPort;
    QByteArray trameCourante;
};
#endif // INTERFACEPRINCIPALE_H
