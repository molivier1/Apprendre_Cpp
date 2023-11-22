#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculatrice; }
QT_END_NAMESPACE

class Calculatrice : public QWidget
{
    Q_OBJECT

public:
    Calculatrice(QWidget *parent = nullptr);
    ~Calculatrice();

private slots:
    void on_pushButtonClear_clicked();

    void on_pushButtonEgal_clicked();

    void onQPushButtonClicked();

private:
    Ui::Calculatrice *ui;
};
#endif // CALCULATRICE_H
