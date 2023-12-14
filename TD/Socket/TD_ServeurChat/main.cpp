#include "interfaceserveurtchat.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceServeurTchat w;
    w.show();
    return a.exec();
}
