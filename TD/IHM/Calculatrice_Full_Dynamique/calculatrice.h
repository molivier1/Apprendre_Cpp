#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculatrice; }
QT_END_NAMESPACE

class Calculatrice : public QWidget
{
    Q_OBJECT

public:
    Calculatrice(QWidget *parent = nullptr);
    ~Calculatrice();
    QPushButton *touches[16];
    QLineEdit *afficheur;
    QGridLayout *grille;
    const QString tableDesSymboles[16]={"7","8","9","+","4","5","6","-","1","2","3","*","c","0","=","/"};
    void onQPushButtonClicked();

private:
    Ui::Calculatrice *ui;
};
#endif // CALCULATRICE_H
