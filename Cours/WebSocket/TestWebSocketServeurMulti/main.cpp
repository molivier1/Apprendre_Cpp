#include "serveurmulti.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServeurMulti w;
    w.show();
    return a.exec();
}
