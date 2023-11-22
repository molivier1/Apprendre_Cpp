#ifndef IHM_DIGICODE_H
/*
* File: ihm_digicode.h
* Author: molivier
*
* Created on 15 novembre 2023, 13:40
* Modified on 11 octobre 2019, 15:20
* Description : Digicode à plusieurs mode
*
*/

#define IHM_DIGICODE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class IHM_Digicode; }
QT_END_NAMESPACE

class IHM_Digicode : public QWidget
{
    Q_OBJECT

public:
    IHM_Digicode(QWidget *parent = nullptr);
    ~IHM_Digicode();
    void gestionModeAdmin();
    void gestionModeNormal();

private:
    Ui::IHM_Digicode *ui;
    QPushButton *touches[12];
    QLineEdit *afficheur;
    QGridLayout *grille;
    void onQPushButton_Clicked();
    QString codeOuverture = "1234";
    const QString codeAdmin = "7777";
    bool modeAdmin;
};
#endif // IHM_DIGICODE_H
