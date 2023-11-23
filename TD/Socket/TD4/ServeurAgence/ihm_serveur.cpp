#include "ihm_serveur.h"
#include "ui_ihm_serveur.h"

IHM_Serveur::IHM_Serveur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IHM_Serveur)
{
    ui->setupUi(this);
}

IHM_Serveur::~IHM_Serveur()
{
    delete ui;
}

