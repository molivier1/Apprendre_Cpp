#include "france2018bdd.h"
#include "ui_france2018bdd.h"

France2018BDD::France2018BDD(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::France2018BDD)
{
    ui->setupUi(this);

    bdd = QSqlDatabase::addDatabase("QMYSQL");
    bdd.setHostName("172.18.58.7");
    bdd.setDatabaseName("france2018");
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

France2018BDD::~France2018BDD()
{
    delete ui;
}


void France2018BDD::on_pushButtonNomDepartement_clicked()
{
    QSqlQuery requetePrepare;
    requetePrepare.prepare("select name from departments where code = :code;");

    requetePrepare.bindValue(":code", ui->lineEditNumero->text());
    if(!requetePrepare.exec())
    {
        qDebug() << "pb requete" << requetePrepare.lastError();
    }

    QString nomDepartement;

    while(requetePrepare.next())
    {
        nomDepartement = requetePrepare.value("name").toString();
        //qDebug() << nomDepartement;
        ui->labelNomDepartement->setText(nomDepartement);
    }
}

