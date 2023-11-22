#include "calculatrice.h"
#include "ui_calculatrice.h"
#include <QJSEngine>
#include <QJSValue>

Calculatrice::Calculatrice(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculatrice)
{
    ui->setupUi(this);

    connect(ui->pushButton0, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton1, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton2, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton3, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton4, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton5, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton6, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton7, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton8, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButton9, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButtonPlus, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButtonMoins, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButtonMultiplier, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    connect(ui->pushButtonDiviser, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
}

Calculatrice::~Calculatrice()
{
    delete ui;
}


void Calculatrice::on_pushButtonClear_clicked()
{
    ui->lineEditAfficheur->setText("");
}


void Calculatrice::on_pushButtonEgal_clicked()
{
    QJSEngine myEngine;
    ui->lineEditAfficheur->setText(myEngine.evaluate(ui->lineEditAfficheur->text()).toString());
}


void Calculatrice::onQPushButtonClicked()
{
    QPushButton *touche;
    touche=qobject_cast<QPushButton*>(sender());
    ui->lineEditAfficheur->insert(touche->text());
}
