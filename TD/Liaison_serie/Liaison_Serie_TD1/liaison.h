#ifndef LIAISON_H
#define LIAISON_H

#include <QSerialPort>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Liaison; }
QT_END_NAMESPACE

class Liaison : public QMainWindow
{
    Q_OBJECT


public:
    Liaison(QWidget *parent = nullptr);
    ~Liaison();


private slots:

    void onReadyRead();
    void on_pushButtonOuvrirPort_clicked();

    void on_pushButton_clicked();

private:
    Ui::Liaison *ui;
    QSerialPort lePortSerie;
};
#endif // LIAISON_H
