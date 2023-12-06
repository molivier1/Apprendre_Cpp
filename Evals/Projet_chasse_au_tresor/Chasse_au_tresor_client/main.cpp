/*
* File: main.cpp
* Author: molivier
*
* Created on 06 decembre 2023, 13:45
* Modified on 06 decembre 2023, 16:30
* Description : Client crawler
*
*/

#include "clientcrawler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientCrawler w;
    w.show();
    return a.exec();
}
