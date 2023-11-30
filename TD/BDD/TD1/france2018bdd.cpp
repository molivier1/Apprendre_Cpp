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

    ui->comboBoxRegions->addItem("Choisissez une région");

    QSqlQuery requeteRegions("select code, name from regions order by name;" );
    if (!requeteRegions.exec()){
        qDebug()<<"pb requete "<<requeteRegions.lastError();
    }
    QString nom;
    QString id;

    while(requeteRegions.next())
    {
        nom=requeteRegions.value("name").toString();
        id=requeteRegions.value("code").toString();
        ui->comboBoxRegions->addItem(nom,id);
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


void France2018BDD::on_comboBoxRegions_currentIndexChanged(int index)
{
    // recupere l'id de la region
    QString idRegion=ui->comboBoxRegions->itemData(index).toString();
    // vider la liste des departements
    ui->comboBoxDepartements->clear();
    ui->comboBoxDepartements->addItem("Choisissez un département");


    QSqlQuery requeteDepartements;
    requeteDepartements.prepare("select code, name from departments "
                                "where region_code = :code order by name;");

    requeteDepartements.bindValue(":code", idRegion);
    if(!requeteDepartements.exec())
    {
        qDebug() << "pb requete" << requeteDepartements.lastError();
    }

    QString nomDepartement;
    QString codeDepartement;

    while(requeteDepartements.next())
    {
        nomDepartement = requeteDepartements.value("name").toString();
        codeDepartement=requeteDepartements.value("code").toString();
        ui->comboBoxDepartements->addItem(nomDepartement, codeDepartement);
    }
}


void France2018BDD::on_comboBoxDepartements_currentIndexChanged(int index)
{
    // recupere l'id de la region
    QString idDepartement=ui->comboBoxDepartements->itemData(index).toString();
    // vider la liste des villes
    ui->comboBoxVilles->clear();
    ui->comboBoxVilles->addItem("Choisissez une ville");


    QSqlQuery requeteVilles;
    requeteVilles.prepare("select name from cities "
                                "where department_code = :code order by name;");

    requeteVilles.bindValue(":code", idDepartement);
    if(!requeteVilles.exec())
    {
        qDebug() << "pb requete" << requeteVilles.lastError();
    }

    QString nomVille;

    while(requeteVilles.next())
    {
        nomVille = requeteVilles.value("name").toString();
        ui->comboBoxVilles->addItem(nomVille);
    }
}

