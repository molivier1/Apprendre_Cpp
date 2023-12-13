#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    maScene.setSceneRect(0,0, 500, 500);
    maBoule=new QGraphicsBouleHorizontalItem(0,0,10,10);
    maBoule->setPos(20,60);
    maScene.addItem(maBoule);
    ui->maVue->fitInView(maScene.sceneRect(), Qt::KeepAspectRatio);
    ui->maVue->setScene(&maScene);

    connect(&timer, &QTimer::timeout, &maScene, &QGraphicsScene::advance);
    timer.start(30);
    setFocus();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        qDebug()<<"gauche";
        break;
    case Qt::Key_Right:
        qDebug()<<"droit";
        break;
    case Qt::Key_Up:
        qDebug()<<"haut";
        break;
    case Qt::Key_Down:
        qDebug()<<"bas";
        break;
    }

    QList <QGraphicsItem *> listeObjCollision = maScene.collidingItems();
    if(listeObjCollision.count() > 0)
    {

    }
}
