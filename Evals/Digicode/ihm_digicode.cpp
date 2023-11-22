/*
* File: ihm_digicode.cpp
* Author: molivier
*
* Created on 15 novembre 2023, 13:40
* Modified on 11 octobre 2019, 15:20
* Description : Digicode à plusieurs mode
*
*/

#include "ihm_digicode.h"
#include "ui_ihm_digicode.h"
#include <QTimer>

IHM_Digicode::IHM_Digicode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IHM_Digicode)
{
    ui->setupUi(this);

    setFixedSize(QSize(274,446));
    int colonne=0, ligne=0;
    grille = new QGridLayout(this);
    afficheur = new QLineEdit(this);
    afficheur->setReadOnly(true);
    afficheur->setAlignment(Qt::AlignRight);
    afficheur->setEchoMode(QLineEdit::Password);
    afficheur->setMinimumHeight(80);
    afficheur->setPlaceholderText("Entrez un code");
    afficheur->setStyleSheet("background-color : #ffffff");

    // effacer le contenu de l'afficheur
    afficheur->clear();

    // ajouter l'afficheur dans le gridLayout
    grille->addWidget(afficheur,ligne,colonne,1,3);

    // Création du clavier
    QString TableDesSymboles[4][3] = {{"7","8","9"},{"4","5","6"},{"1","2","3"},{"On","0","Ok"}};

    // Initialisation et positionnement des différentes touches sur la grille
    int cmp = 0;
    for (ligne = 1; ligne < 5; ligne++)
    {
        for (colonne = 0; colonne < 3; colonne ++)
        {
            touches[cmp] = new QPushButton;
            grille->addWidget(touches[cmp],ligne,colonne); //(y,x,rowspan,colspan)
            touches[cmp]->setText(TableDesSymboles[ligne-1][colonne]);
            touches[cmp]->setFixedSize(QSize(80,80));
            connect(touches[cmp], &QPushButton::clicked, this, &IHM_Digicode::onQPushButton_Clicked);
            cmp++;
        }
    }

    this->setLayout(grille);
}

IHM_Digicode::~IHM_Digicode()
{
    delete ui;
}

void IHM_Digicode::onQPushButton_Clicked()
{
    // On récupère la touche qui vient d'être appuyé en la stockant
    // dans la variable touche de type QPushButton
    QPushButton *touche;
    touche=qobject_cast<QPushButton*>(sender());

    // Si la touche n'est pas un numéro alors on va tester si c'est "On" ou "Ok",
    // sinon on va essayer d'écrire la numéro dans l'afficheur
    if(touche->text() == "On" || touche->text() == "Ok")
    {
        if(touche->text() == "Ok")
        {
            // Si modeAdmin est true alors on va dans gestionModeAdmin,
            // sinon on va dans gestionModeNormal
            if (modeAdmin)
            {
                gestionModeAdmin();
            }
            else
            {
                gestionModeNormal();
            }
        }
        else
        {
            afficheur->setPlaceholderText("Entrez un code");
            afficheur->setStyleSheet("background-color: white;");
            afficheur->clear();
        }
    }
    else
    {
        // Si la longueur du texte est < 4 alors on écrit,
        // sinon on n'écrit pas et on ajoute une couleur rouge au texte
        if(afficheur->text().length() < 4)
        {
            afficheur->insert(touche->text());
        }
        else
        {
            // Vérifie que "color: red;" n'est pas déjà présent dans le css
            // afin d'éviter une grosse répétition
            if(!afficheur->styleSheet().contains("color: red;"))
            {
                // Ajout de la couleur rouge au css déjà présent
                afficheur->setStyleSheet("color: red;" + afficheur->styleSheet());
            }
        }
    }
}

void IHM_Digicode::gestionModeAdmin()
{
    modeAdmin=false;
    // Si le nouveau code à une longueur supérieur à 3 et qu'il est différent du code admin
    // alors on sauvegarde ce nouveau,
    // sinon on ne le sauvegarde pas et on avertit l'utilisateur
    if(afficheur->text().length() > 3 && afficheur->text() != codeAdmin)
    {
        codeOuverture=afficheur->text();
        afficheur->setPlaceholderText("Nouveau code ouverture accepté");
        afficheur->clear();
        QTimer *timer=new QTimer(this);
        connect(timer,&QTimer::timeout,this,[=](){
            afficheur->setPlaceholderText("Entrez un code");
            afficheur->setStyleSheet("background-color : #ffffff");
            timer->stop();
            timer->deleteLater();
        });
        timer->start(3000);
    }
    else
    {
        // Changement du message en fonction de l'erreur
        if (afficheur->text() == codeAdmin)
        {
            afficheur->setPlaceholderText("Nouveau code doit être != codeAdmin");
        }
        else
        {
            afficheur->setPlaceholderText("Longueur nouveau code doit être = 4");
        }

        // bg -> light orange
        afficheur->setStyleSheet("background-color: #FFD580;");
        afficheur->clear();
    }
}

void IHM_Digicode::gestionModeNormal()
{
    // Si le code dans l'afficheur est bon alors on valide,
    // sinon on test si c'est le codeAdmin
    if (afficheur->text() == codeOuverture)
    {
        afficheur->setPlaceholderText("Code ouverture OK");
        // bg -> light green
        afficheur->setStyleSheet("background-color: #90EE90;");
        afficheur->clear();
    }
    else
    {
        // Si c'est le codeAdmin alors on lance le mode admin,
        // sinon on affiche que ce code est inconnu
        if (afficheur->text() == codeAdmin)
        {
            modeAdmin = true;
            afficheur->setPlaceholderText("Mode admin");
            // bg -> light yellow
            afficheur->setStyleSheet("background-color: #FFFFED;");
            afficheur->clear();
        }
        else
        {
            afficheur->setPlaceholderText("Code inconnu");
            // bg -> light red
            afficheur->setStyleSheet("background-color: #FF7F7F;");
            afficheur->clear();
        }
    }
}
