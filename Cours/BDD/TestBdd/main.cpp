#include "widgettestbdd.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetTestBDD w;
    w.show();
    return a.exec();
}
