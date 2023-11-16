#include "dialogconfigurerliaisongps.h"
#include "ui_dialogconfigurerliaisongps.h"
#include <QSerialPortInfo>
#include <QPushButton>

DialogConfigurerLiaisonGPS::DialogConfigurerLiaisonGPS(QSerialPort &_lePort, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfigurerLiaisonGPS),
    lePort(_lePort)
{
    ui->setupUi(this);
    // Afficher tous les ports disponibles dans le comBoxPort
    ui->comboBoxPort->addItem("Choisissez un port");
    for(const auto &info : QSerialPortInfo::availablePorts() ) // foreach
    {
            ui->comboBoxPort->addItem(info.portName());
    }
    // Afficher toutes les vitesses dans le comboBoxVitesse
    int valComboBoxVitesse[8] = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
    for(int i = 0; i < 8; i++)
    {
        ui->comboBoxVitesse->addItem(QString::number(valComboBoxVitesse[i]));
    }
    // Index comBoxVitesse mit à 3 par défaut
    ui->comboBoxVitesse->setCurrentIndex(3);
    // Nombre de bits de données à 8 par défaut
    lePort.setDataBits(QSerialPort::Data8);
    // Pas de parité par défaut
    lePort.setParity(QSerialPort::NoParity);
    // 1 bit de stop par défaut
    lePort.setStopBits(QSerialPort::OneStop);
    // Pas de contrôle de flux par défaut
    lePort.setFlowControl(QSerialPort::NoFlowControl);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

DialogConfigurerLiaisonGPS::~DialogConfigurerLiaisonGPS()
{
    delete ui;
}

void DialogConfigurerLiaisonGPS::on_spinBoxBigData_valueChanged(int arg1)
{
    lePort.setDataBits(static_cast<QSerialPort::DataBits>(arg1));
}


void DialogConfigurerLiaisonGPS::on_comboBoxVitesse_currentTextChanged(const QString &arg1)
{
    lePort.setBaudRate(arg1.toInt());
}


void DialogConfigurerLiaisonGPS::on_checkBoxStop_toggled(bool checked)
{
    if(checked)
    {
        // Mettre 2 bits de stop
        lePort.setStopBits(QSerialPort::TwoStop);
    }
    else
    {
        // Mettre 1 bit de stop
        lePort.setStopBits(QSerialPort::OneStop);
    }
}


void DialogConfigurerLiaisonGPS::on_radioButtonPaire_toggled(bool checked)
{
    if(checked)
    {
        lePort.setParity(QSerialPort::EvenParity);
    }
}


void DialogConfigurerLiaisonGPS::on_radioButtonImpaire_toggled(bool checked)
{
    if(checked)
    {
        lePort.setParity(QSerialPort::OddParity);
    }
}


void DialogConfigurerLiaisonGPS::on_radioButtonNone_toggled(bool checked)
{
    if(checked)
    {
        lePort.setParity(QSerialPort::NoParity);
    }
}


void DialogConfigurerLiaisonGPS::on_comboBoxPort_currentIndexChanged(int index)
{
    if(index!=0)
    {
        lePort.setPortName(ui->comboBoxPort->currentText());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
