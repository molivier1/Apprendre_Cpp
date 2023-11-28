#include "widgettestbdd.h"
#include "ui_widgettestbdd.h"

WidgetTestBDD::WidgetTestBDD(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetTestBDD)
{
    ui->setupUi(this);

    bdd = QSqlDatabase::addDatabase("QMYSQL");
    bdd.setHostName("172.18.58.7");
    bdd.setDatabaseName("france2015");
    bdd.setUserName("snir");
    bdd.setPassword("snir");

    if (!bdd.open())
    {
        QMessageBox::warning(this, "Erreur connection bdd", bdd.lastError().text());
    }
    else
    {
        qDebug() << "Ouverture de la base de donnée " << bdd.databaseName();
    }
}

WidgetTestBDD::~WidgetTestBDD()
{
    delete ui;
}


void WidgetTestBDD::on_pushButtonConnexion_clicked()
{
    QSqlQuery requete("select departement_nom from departements;");
    if(!requete.exec())
    {
        qDebug() << "pb requete" << requete.lastError();
    }

    int nbLignes = requete.size();
    qDebug() << "nombre departements : " << nbLignes;
    QString nomDepartement;
    while (requete.next())
    {
        nomDepartement = requete.value("departement_nom").toString();
        qDebug() << nomDepartement;
    }
}

