#ifndef DESSIN_H
#define DESSIN_H

#include <QWidget>

#include <QGraphicsWidget>
#include <QPen>
#include <QGraphicsView>
#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dessin;
}
QT_END_NAMESPACE

class Dessin : public QWidget
{
    Q_OBJECT

public:
    Dessin(QWidget *parent = nullptr);
    ~Dessin();

private slots:
    void on_pushButtonRectangleBleu_clicked();

private:
    Ui::Dessin *ui;

    QGraphicsScene *scene;
};
#endif // DESSIN_H
