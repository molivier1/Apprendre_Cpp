#include "widget.h"
#include "ui_widget.h"
#include <QRandomGenerator>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene.setSceneRect(0,0,300,200);

    // creation de mon objet ayant advance et gestion de collision
    maBoule=new QGraphicsBalleCollisionItem(0,0,10,10);
    maBoule->setBrush(QBrush(Qt::red));
    maBoule->setPos(10,10);
    scene.addItem(maBoule);

    ui->vue->fitInView(scene.sceneRect(),Qt::KeepAspectRatio);
    ui->vue->setScene(&scene);
    ui->vue_2->setScene(&scene);
    ui->vue_3->setScene(&scene);
    ui->vue_4->setScene(&scene);

    ui->vue_2->rotate(180);

    QRadialGradient brushRadialGradient(150, 200, 250);
    brushRadialGradient.setColorAt(0, Qt::yellow);
    brushRadialGradient.setColorAt(1, Qt::red);
    ui->vue_3->setBackgroundBrush(brushRadialGradient);

    ui->vue_4->setBackgroundBrush(Qt::DiagCrossPattern);
    // association de timeout du timer au slot advance des objects
    connect(&timer,&QTimer::timeout,&scene,&QGraphicsScene::advance);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonLancerAnim_clicked()
{
    // lancement du timer -> timeout toutes les 30 millisecondes
    timer.start(30);
}
