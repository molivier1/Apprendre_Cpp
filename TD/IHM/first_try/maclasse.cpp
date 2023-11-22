#include "maclasse.h"
#include "ui_maclasse.h"

MaClasse::MaClasse(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MaClasse)
{
    ui->setupUi(this);
}

MaClasse::~MaClasse()
{
    delete ui;
}


void MaClasse::on_pushButton_2_clicked()
{
    ui->pushButton->setText("Bonjour le monde");
}
