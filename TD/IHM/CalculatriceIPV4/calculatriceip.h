#ifndef CALCULATRICEIP_H
#define CALCULATRICEIP_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CalculatriceIP; }
QT_END_NAMESPACE

class CalculatriceIP : public QWidget
{
    Q_OBJECT

public:
    CalculatriceIP(QWidget *parent = nullptr);
    ~CalculatriceIP();

private:
    Ui::CalculatriceIP *ui;
};
#endif // CALCULATRICEIP_H
