#include "liaison.h"
#include "ui_liaison.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>



Liaison::Liaison(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Liaison)
{
    ui->setupUi(this);
    for(const auto &info : QSerialPortInfo::availablePorts() ) // foreach
    {
            ui->comboBoxChoixPort->addItem(info.portName());
    }
}

Liaison::~Liaison()
{
    delete ui;
}



void Liaison::on_pushButtonOuvrirPort_clicked()
{
    if(ui->pushButtonOuvrirPort->text() == "Fermer le port"){
        ui->pushButtonOuvrirPort->setText("Ouvrir le port Serie");
    }else{
        ui->pushButtonOuvrirPort->setText("Fermer le port");
        if(ui->comboBoxChoixPort->currentIndex() != 0){
            lePortSerie.setPortName(ui->comboBoxChoixPort->currentText());
            lePortSerie.setBaudRate(QSerialPort::Baud115200);
            lePortSerie.setDataBits(QSerialPort::Data8);
            lePortSerie.setParity(QSerialPort::NoParity);
            lePortSerie.setStopBits(QSerialPort::OneStop);
            if(lePortSerie.open(QIODevice::ReadWrite)){
                qDebug() << "Le port série est ouvert";
                connect(&lePortSerie, &QSerialPort::readyRead, this, &Liaison::onReadyRead);
            }else{
                QMessageBox erreur;
                erreur.setText("Veuillez sélectionner un port");
                erreur.exec();
            }
        }
    }
}

void Liaison::onReadyRead(){
    QByteArray reception;
    while(lePortSerie.bytesAvailable() > 0){
        reception = lePortSerie.readAll();
        ui->textEditRecu->append(reception);
    }
}
void Liaison::on_pushButton_clicked()
{
    QString message = ui->lineEditEnvoi->text();
    if(message.length() != 0){
        lePortSerie.write(message.toLatin1());
    }
}

