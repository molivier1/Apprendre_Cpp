#include "calculatrice.h"
#include "ui_calculatrice.h"
#include <QJSEngine>
#include <QJSValue>

Calculatrice::Calculatrice(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculatrice)
{
    ui->setupUi(this);
    int colonne=0, ligne=0;
    grille=new QGridLayout();
    afficheur=new QLineEdit();
    afficheur->setReadOnly(true);
    //afficheur->setAlignment(Qt::AlignRight);
    grille->addWidget(afficheur,ligne,colonne,1,4); //(y,x,rowspan,colspan)


    int cmp = 0;
    for(ligne=1; ligne < 5; ligne++)
    {
        for(colonne = 0; colonne < 4; colonne++)
        {
            touches[cmp] = new QPushButton;
            grille->addWidget(touches[cmp],ligne,colonne); //(y,x,rowspan,colspan)
            touches[cmp]->setText(tableDesSymboles[cmp]);
            connect(touches[cmp], &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
            cmp++;
        }
    }

    // ajout du layout à l'interface principale
    this->setLayout(grille);
}

Calculatrice::~Calculatrice()
{
    delete ui;
}

void Calculatrice::onQPushButtonClicked()
{
    QPushButton *touche;
    touche=qobject_cast<QPushButton*>(sender());
    QJSEngine myEngine;
    if(touche->text() == "=" || touche->text() == "c")
    {
        if(touche->text() == "=")
        {
            afficheur->setText(myEngine.evaluate(afficheur->text()).toString());
        }
        else
        {
            afficheur->clear();
        }
    }
    else
    {
        afficheur->insert(touche->text());
    }
}
