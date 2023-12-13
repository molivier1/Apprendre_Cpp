#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "qgraphicsballecollisionitem.h"

#define LARGEUR 640
#define HAUTEUR 360
#define NBOBSTACLES 50
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonLancerAnim_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene scene;
    QGraphicsBalleCollisionItem *maBoule;
    QTimer timer;
    QGraphicsRectItem *obstacles[NBOBSTACLES];

};

#endif // WIDGET_H
