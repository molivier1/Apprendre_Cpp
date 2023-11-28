#ifndef WIDGETTESTBDD_H
#define WIDGETTESTBDD_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetTestBDD; }
QT_END_NAMESPACE

class WidgetTestBDD : public QWidget
{
    Q_OBJECT

public:
    WidgetTestBDD(QWidget *parent = nullptr);
    ~WidgetTestBDD();

private slots:
    void on_pushButtonConnexion_clicked();

private:
    Ui::WidgetTestBDD *ui;
    QSqlDatabase bdd;
};
#endif // WIDGETTESTBDD_H
