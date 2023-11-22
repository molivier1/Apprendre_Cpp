#include "calculatriceip.h"
#include "ui_calculatriceip.h"

CalculatriceIP::CalculatriceIP(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CalculatriceIP)
{
    ui->setupUi(this);
    for(int i = 8; i < 31; i++)
    {

    }
}

CalculatriceIP::~CalculatriceIP()
{
    delete ui;
}

