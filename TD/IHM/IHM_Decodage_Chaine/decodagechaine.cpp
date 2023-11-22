#include "decodagechaine.h"
#include "ui_decodagechaine.h"

DecodageChaine::DecodageChaine(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DecodageChaine)
{
    ui->setupUi(this);
}

DecodageChaine::~DecodageChaine()
{
    delete ui;
}


void DecodageChaine::on_pushButtonDecoder_clicked()
{
    // Récupérer le texte de l'objet lineEditTexteADecoder
    QString texte=ui->lineEditTexteADecoder->text();
    // Découper le texte selon le ";" et mettre chaque champs dans le "tableau" tab
    QStringList tab=texte.split(";");
    if(tab.length() > 4){
        ui->lineEditNom->setText(tab.at(0));
        ui->lineEditPrenom->setText(tab.at(1));
        ui->lineEditAge->setText(tab.at(2));
        ui->lineEditPoids->setText(tab.at(3));
        ui->lineEditTaille->setText(tab.at(4));
    }

}

