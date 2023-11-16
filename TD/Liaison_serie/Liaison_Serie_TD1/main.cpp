#include "liaison.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Liaison w;
    w.show();
    return a.exec();
}
