#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBoxWindows_clicked()
{
    if(ui->checkBoxWindows->isChecked())
    {
        ui->textEdit->append("Windows coche");
    }
    else
    {
        ui->textEdit->append("Windows decoche");
    }
}

void MainWindow::on_checkBoxOSXLion_clicked()
{
    if(ui->checkBoxOSXLion->isChecked())
    {
        ui->textEdit->append("OS X Lion coche");
    }
    else
    {
        ui->textEdit->append("OS X Lion decoche");
    }
}


void MainWindow::on_checkBoxLinux_clicked()
{
    if(ui->checkBoxLinux->isChecked())
    {
        ui->textEdit->append("Linux coche");
    }
    else
    {
        ui->textEdit->append("Linux decoche");
    }
}


void MainWindow::on_radioButtonWindows_clicked()
{
    ui->textEdit->append("Radio Windows");
}


void MainWindow::on_radioButtonOSXLion_clicked()
{
    ui->textEdit->append("Radio OS X Lion");
}


void MainWindow::on_radioButtonLinux_clicked()
{
    ui->textEdit->append("Radio OS X Linux");
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->textEdit->append(arg1);
}


void MainWindow::on_pushButtonWindows_clicked()
{
    ui->textEdit->append("Bouton Windows");
}


void MainWindow::on_pushButtonOSXLion_clicked()
{
    ui->textEdit->append("Bouton OS X Lion");
}


void MainWindow::on_pushButtonLinux_clicked()
{
    ui->textEdit->append("Bouton Linux");
}


void MainWindow::on_lineEditCode_textChanged(const QString &arg1)
{
    ui->textEdit->append(arg1);
}


void MainWindow::on_actionC_triggered()
{
    ui->textEdit->append("C");
}


void MainWindow::on_actionJava_triggered()
{
    ui->textEdit->append("Java");
}


void MainWindow::on_actionCpp_triggered()
{
    ui->textEdit->append("C++");
}


void MainWindow::on_actionPHP_triggered()
{
    ui->textEdit->append("PHP");
}


void MainWindow::on_actionJavascript_triggered()
{
    ui->textEdit->append("Javascript");
}

