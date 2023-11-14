#ifndef TESTINI_H
#define TESTINI_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Testini; }
QT_END_NAMESPACE

class Testini : public QWidget
{
    Q_OBJECT

public:
    Testini(QWidget *parent = nullptr);
    ~Testini();

private slots:
    void on_pushButtonCreation_clicked();

    void on_pushButtonLireFichier_clicked();

    void on_pushButtonEcrireBinaire_clicked();

    void on_pushButtonLireBinaire_clicked();

private:
    Ui::Testini *ui;
};
#endif // TESTINI_H
