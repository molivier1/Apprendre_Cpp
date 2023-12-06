/*
* File: main.cpp
* Author: molivier
*
* Created on 06 decembre 2023, 13:45
* Modified on 06 decembre 2023, 16:30
* Description : Serveur multiclient crawler
*
*/

#include "serveurcrawler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServeurCrawler w;
    w.show();
    return a.exec();
}
