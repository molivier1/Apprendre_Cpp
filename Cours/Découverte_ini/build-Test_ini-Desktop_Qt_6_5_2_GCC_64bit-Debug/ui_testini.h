/********************************************************************************
** Form generated from reading UI file 'testini.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTINI_H
#define UI_TESTINI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Testini
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonCreation;
    QPushButton *pushButtonLireFichier;
    QPushButton *pushButtonEcrireBinaire;
    QPushButton *pushButtonLireBinaire;

    void setupUi(QWidget *Testini)
    {
        if (Testini->objectName().isEmpty())
            Testini->setObjectName("Testini");
        Testini->resize(370, 258);
        verticalLayout = new QVBoxLayout(Testini);
        verticalLayout->setObjectName("verticalLayout");
        pushButtonCreation = new QPushButton(Testini);
        pushButtonCreation->setObjectName("pushButtonCreation");

        verticalLayout->addWidget(pushButtonCreation);

        pushButtonLireFichier = new QPushButton(Testini);
        pushButtonLireFichier->setObjectName("pushButtonLireFichier");

        verticalLayout->addWidget(pushButtonLireFichier);

        pushButtonEcrireBinaire = new QPushButton(Testini);
        pushButtonEcrireBinaire->setObjectName("pushButtonEcrireBinaire");

        verticalLayout->addWidget(pushButtonEcrireBinaire);

        pushButtonLireBinaire = new QPushButton(Testini);
        pushButtonLireBinaire->setObjectName("pushButtonLireBinaire");

        verticalLayout->addWidget(pushButtonLireBinaire);


        retranslateUi(Testini);

        QMetaObject::connectSlotsByName(Testini);
    } // setupUi

    void retranslateUi(QWidget *Testini)
    {
        Testini->setWindowTitle(QCoreApplication::translate("Testini", "Testini", nullptr));
        pushButtonCreation->setText(QCoreApplication::translate("Testini", "Cr\303\251ation ini", nullptr));
        pushButtonLireFichier->setText(QCoreApplication::translate("Testini", "LireFichier", nullptr));
        pushButtonEcrireBinaire->setText(QCoreApplication::translate("Testini", "Ecrire binaire", nullptr));
        pushButtonLireBinaire->setText(QCoreApplication::translate("Testini", "Lire binaire", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Testini: public Ui_Testini {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTINI_H
