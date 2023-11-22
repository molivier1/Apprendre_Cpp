#include "decodagechaine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DecodageChaine w;
    w.show();
    return a.exec();
}
