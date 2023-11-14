#include "testini.h"
#include "ui_testini.h"
#include <QDebug>
#include <QSettings>
#include <QFileInfo>
#include <QFileDialog>

Testini::Testini(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Testini)
{
    ui->setupUi(this);
    QString adresseIp;
    int numeroPort;
    QChar h, d, j;
    QString nomFichierIni = qApp->applicationName()+".ini";
    QFileInfo testFichier(nomFichierIni);
    if(testFichier.exists() && testFichier.isFile())
    {
        QSettings paramSocket(nomFichierIni, QSettings::IniFormat);
        adresseIp = paramSocket.value("CONFIG/ip", "172.18.58.15").toString();
        numeroPort = paramSocket.value("CONFIG/port").toInt();
        d = paramSocket.value("COMMANDES/date").toString().at(0);
        h = paramSocket.value("COMMANDES/heure").toString().at(0);
        j = paramSocket.value("COMMANDES/jour").toString().at(0);
        qDebug() << adresseIp << numeroPort << h << d << j;
    }
    else
    {
        qDebug() << "Fichier ini non trouvé";
    }
}

Testini::~Testini()
{
    delete ui;
}


void Testini::on_pushButtonCreation_clicked()
{
    QString nomFichierIni = qApp->applicationName()+".ini";
    QSettings paramSocket(nomFichierIni, QSettings::IniFormat);

    paramSocket.beginGroup("CONFIG");
    paramSocket.setValue("ip", "192.168.0.2");
    paramSocket.setValue("port", "9999");
    paramSocket.endGroup();

    paramSocket.beginGroup("COMMANDES");
    paramSocket.setValue("heure", "1");
    paramSocket.setValue("date", "2");
    paramSocket.setValue("jour", "3");
    paramSocket.endGroup();
}


void Testini::on_pushButtonLireFichier_clicked()
{
    QFile fichier(qApp->applicationName()+".ini");
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << fichier.errorString();
    }
    else
    {
        QString line;
        QTextStream in(&fichier);
        while(!in.atEnd())
        {
            in >> line;
            // Autre possibilité :
            // QString line = in.readLine();
            qDebug() << line;
        }
    }
}


void Testini::on_pushButtonEcrireBinaire_clicked()
{
    QFile fichierSortieBinaire("monfichier.bin");
    if(!fichierSortieBinaire.open(QIODevice::WriteOnly))
    {
        qDebug() << fichierSortieBinaire.errorString();
    }
    else
    {
        QDataStream out(&fichierSortieBinaire);
        QString nom = "Bidochon";
        QString prenom = "Robert";
        int age = 54;
        double taille = 1.65;
        QChar sexe = 'M';
        out << nom << prenom << age << taille << sexe;
        fichierSortieBinaire.close();
    }
}

void Testini::on_pushButtonLireBinaire_clicked()
{
    QString nomFichier = QFileDialog::getOpenFileName(this,
                                                      tr("Ouvrir fichier"),
                                                      "/home/mateo/Documents/SNIR_2/Code/C++/IHM",
                                                      tr("Fichiers binaires (*.bin)"));
    QFile fichierEntreeBinaire(nomFichier);
    if(!fichierEntreeBinaire.open(QIODevice::ReadOnly))
    {
        qDebug() << fichierEntreeBinaire.errorString();
    }
    else
    {
        QDataStream in(&fichierEntreeBinaire);
        QString nom;
        QString prenom;
        int age;
        double taille;
        QChar sexe;
        in >> nom >> prenom >> age >> taille >> sexe;
        fichierEntreeBinaire.close();
        qDebug() << nom << prenom << age << taille << sexe;
    }
}

