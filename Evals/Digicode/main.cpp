/*
* File: main.cpp
* Author: molivier
*
* Created on 15 novembre 2023, 13:40
* Modified on 11 octobre 2019, 15:20
* Description : Digicode à plusieurs mode
*
*/

#include "ihm_digicode.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHM_Digicode w;
    w.show();
    return a.exec();
}
