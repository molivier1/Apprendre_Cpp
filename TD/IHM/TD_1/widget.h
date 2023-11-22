#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonSuite_clicked();

    void on_pushButtonDevine_clicked();

    void on_pushButtonLorentz_clicked();

    void on_pushButtonLorentzAge_clicked();

private:
    Ui::Widget *ui;

    void afficherInfos();
    double poids;
    double taille;
    QString nom;
    QString prenom;
    int age;
    static const int NBIMC=6;
    static const int NBCORPULENCE=7;
};
#endif // WIDGET_H
