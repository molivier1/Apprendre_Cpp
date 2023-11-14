#include "testini.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Testini w;
    w.show();
    return a.exec();
}
