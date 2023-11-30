#ifndef FRANCE2018BDD_H
#define FRANCE2018BDD_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class France2018BDD; }
QT_END_NAMESPACE

class France2018BDD : public QWidget
{
    Q_OBJECT

public:
    France2018BDD(QWidget *parent = nullptr);
    ~France2018BDD();

private slots:
    void on_pushButtonNomDepartement_clicked();

    void on_comboBoxRegions_currentIndexChanged(int index);

    void on_comboBoxDepartements_currentIndexChanged(int index);

private:
    Ui::France2018BDD *ui;
    QSqlDatabase bdd;
};
#endif // FRANCE2018BDD_H
