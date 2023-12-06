#include "dessin.h"
#include "ui_dessin.h"

Dessin::Dessin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dessin)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,400,300);

    // Association scene<->vue
    ui->vue->setScene(scene);
}

Dessin::~Dessin()
{
    delete ui;
}

void Dessin::on_pushButtonRectangleBleu_clicked()
{
    // definition du rectangle
    // creation de l'objet
    QGraphicsRectItem *rectangle = new QGraphicsRectItem(0, 0, 100, 50);

    // couleur du contour
    QColor monBleu(153, 204, 255);
    QPen contour(monBleu);

    // couleur de remplissage
    QBrush remplissage(monBleu);

    rectangle->setPen(contour);
    rectangle->setBrush(remplissage);

    // ajout de l'objet à ma scène
    scene->addItem(rectangle);

    rectangle->setPos(200, 100);
}

void Dessin::on_pushButtonTriangle_clicked()
{
    QPolygon unTriangle;
    unTriangle.setPoints(2,
                        );

    QGraphicsPolygonItem *triangle = new QGraphicsPolygonItem(unTriangle);

    QPen contour(Qt::red);
    QBrush remplissage(Qt::blue);

    triangle->setPen(contour);
    triangle->setBrush(remplissage);

    triangle->setScale(35);

    scene->addItem(triangle);

    triangle->setPos(50, 50);
}


void Dessin::on_pushButtonClearScene_clicked()
{
    QList <QGraphicsItem *> listeDesItems = scene->items();
    foreach(QGraphicsItem *it, listeDesItems)
    {
        scene->removeItem(it);
        delete it;
    }
}

