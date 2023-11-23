#include "interfaceprincipale.h"
#include "ui_interfaceprincipale.h"
#include <QMessageBox>
#include <QTime>
#include <QDate>
#include <QTimeZone>
#include <QFileDialog>>


InterfacePrincipale::InterfacePrincipale(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfacePrincipale)
    , configGPS(lePort)
{
    ui->setupUi(this);
    ui->tableWidgetNMEA->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    labelEtatPort.setText("port fermé");
    ui->statusbar->addPermanentWidget(&labelEtatPort);
    ui->statusbar->show();
}

InterfacePrincipale::~InterfacePrincipale()
{
    lePort.close();
    for (int i = 0; i < ui->tableWidgetNMEA->rowCount(); i++)
    {
        delete ui->tableWidgetNMEA->item(i, 0);
        delete ui->tableWidgetNMEA->item(i, 1);
        delete ui->tableWidgetNMEA->item(i, 2);
    }

    delete ui;
}


void InterfacePrincipale::on_actionConfigurer_triggered()
{
    if (configGPS.exec() == QDialog::Accepted)
    { 	// ouverture du port

        if (lePort.isOpen())
        {
            lePort.close();
        }

        if(lePort.open(QIODevice::ReadWrite)){
            QString stringParity = "Erreur";

            switch (lePort.parity())
            {
            case QSerialPort::EvenParity :
                stringParity = "p";
                break;

            case QSerialPort::OddParity :
                stringParity = "i";
                break;
            case QSerialPort::NoParity :
                stringParity = "n";
                break;
            }

            labelEtatPort.setText("Port " + lePort.portName() + ", "
                                  + QString::number(lePort.baudRate()) + ", "
                                  + QString::number(lePort.dataBits()) + ", "
                                  + stringParity + ", "
                                  + QString::number(lePort.stopBits()));

            connect(&lePort, &QSerialPort::readyRead, this, &InterfacePrincipale::onQSerialPort_ReadyRead);
        }else{
            QMessageBox erreur;
            erreur.setText("Veuillez sélectionner un port");
            erreur.exec();
        }
    }
}


void InterfacePrincipale::on_actionEnregistrer_triggered()
{
    // ajouter ici les bons paramètres pour obtenir la figure ci-dessus
    QString nomFichier = QFileDialog::getSaveFileName();
    if (!nomFichier.isEmpty())
    {
        if (!nomFichier.endsWith(".csv", Qt::CaseInsensitive))
        {
            nomFichier += ".csv";
        }

        QFile fichierCSV(nomFichier);

        if (fichierCSV.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream flux(&fichierCSV); // pour l’écriture dans le fichier on utilise les flux
            flux << "Date; Latitude; Longitude\n";
            // Ajouter ici le code pour parcourir le tableWidgetNMEA
            // et stocker dans le fichier chaque élément
            for (int i = 0; i < ui->tableWidgetNMEA->rowCount(); i++)
            {
                flux << ui->tableWidgetNMEA->item(i, 0)->text() << "; "
                     << ui->tableWidgetNMEA->item(i, 1)->text() << "; "
                     << ui->tableWidgetNMEA->item(i, 2)->text() << '\n';
            }
        }
        else
        {
            qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV.";
        }

        fichierCSV.close() ;
        qDebug() << "Enregistrement au format CSV réussi.";
    }
    else
    {
        qDebug() << "L'opération d'enregistrement a été annulée.";
    }

}


void InterfacePrincipale::on_actionOuvrir_triggered()
{

}


void InterfacePrincipale::on_actionA_propos_de_triggered()
{

}

void InterfacePrincipale::onQSerialPort_ReadyRead()
{
    QString string;

    trameCourante.append(lePort.readAll());

    if (trameCourante.count('\n'))
    {
        string = trameCourante.left(trameCourante.indexOf('\n'));
        trameCourante.remove(0, trameCourante.indexOf('\n') + 1);

        ui->textEditTrame->append(string);
        DecodageNMEA(string);
    }
}

void InterfacePrincipale::DecodageNMEA(const QString &_trameNMEA)
{
    QStringList champsNMEA = _trameNMEA.split(',');

    if (champsNMEA.size() >= 12 && champsNMEA.at(0) == "$GPRMC")
    {
        // Extraction de l'heure
        QString heureStr = champsNMEA.at(1);
        QTime heure(heureStr.mid(0, 2).toInt(), heureStr.mid(2, 2).toInt(), heureStr.mid(4, 2).toInt());
        QString dateStr = champsNMEA.at(9);
        QDate date(dateStr.mid(0, 2).toInt(), dateStr.mid(2, 2).toInt(), dateStr.mid(4, 2).toInt());

        // Extraction de la latitude
        QString latitude = champsNMEA.at(3);
        latitude.append('"' + champsNMEA.at(4));

        // Extraction de la longitude
        QString longitude = champsNMEA.at(5);
        longitude.append('"' + champsNMEA.at(6));

        // à compléter pour les autres champs de la trame

        QDateTime horodatage(date, heure, QTimeZone("Europe/Paris"));
        horodatage = horodatage.addSecs(horodatage.offsetFromUtc());

        int ligneCourante = ui->tableWidgetNMEA->rowCount();
        ui->tableWidgetNMEA->insertRow(ligneCourante);
        QTableWidgetItem *dateItem = new QTableWidgetItem(horodatage.toString(Qt::TextDate));
        ui->tableWidgetNMEA->setItem(ligneCourante,0,dateItem);

        // à compléter pour les autres colonnes du tableau
        QTableWidgetItem *latitudeItem = new QTableWidgetItem(latitude);
        ui->tableWidgetNMEA->setItem(ligneCourante, 1, latitudeItem);

        QTableWidgetItem *longitudeItem = new QTableWidgetItem(longitude);
        ui->tableWidgetNMEA->setItem(ligneCourante, 2, longitudeItem);
    }
}
