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
    unTriangle.setPoints(3,
                         75, 45,
                         0, 150,
                         150, 150);

    QGraphicsPolygonItem *triangle = new QGraphicsPolygonItem(unTriangle);

    QPen contour(Qt::red);
    contour.setWidth(2);
    QColor monBleu(153, 204, 255);
    QBrush remplissage(monBleu);

    triangle->setPen(contour);
    triangle->setBrush(remplissage);

    //triangle->setScale(4);

    scene->addItem(triangle);

    triangle->setPos(200, 100);
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


void Dessin::on_pushButtonCercle_clicked()
{
    QGraphicsEllipseItem *cercle = new QGraphicsEllipseItem(0,0,100,100);

    // couleur du contour
    QPen contour(QColor(255,0,255));
    contour.setWidth(3);

    // couleur de remplissage
    QBrush remplissage(Qt::green);

    cercle->setPen(contour);
    cercle->setBrush(remplissage);

    scene->addItem(cercle);

    cercle->setPos(100,200);
}


void Dessin::on_pushButtonEllipse_clicked()
{
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(0, 0, 100, 50);

    QPen pen(Qt::red);
    QBrush brush(Qt::red);

    ellipse->setPen(pen);
    ellipse->setBrush(brush);

    scene->addItem(ellipse);

    ellipse->setPos(10, 250);
}


void Dessin::on_pushButtonEtoile_clicked()
{
    QPolygon uneEtoile;
    uneEtoile.setPoints(10,
                     300, 100,
                     335, 180,
                     425, 180,
                     365, 230,
                     400, 300,
                     300, 250,
                     200, 300,
                     235, 230,
                     175, 180,
                     265, 180);

    QGraphicsPolygonItem *etoileFond = new QGraphicsPolygonItem(uneEtoile);

    QBrush brushVert(Qt::green);

    etoileFond->setBrush(brushVert);

    scene->addItem(etoileFond);

    etoileFond->setPos(125,125);



    QGraphicsPolygonItem *etoile = new QGraphicsPolygonItem(uneEtoile);

    QPen pen(Qt::blue);
    QBrush brush(Qt::BDiagPattern);

    pen.setWidth(4);

    etoile->setPen(pen);
    etoile->setBrush(brush);

    scene->addItem(etoile);

    etoile->setPos(125,125);
}

void Dessin::on_pushButtonQuestion4_clicked()
{
    // Init des variables items
    QGraphicsEllipseItem *cercleLinearGradient = new QGraphicsEllipseItem(0,0,100,100);
    QGraphicsRectItem *carreLinearGradient = new QGraphicsRectItem(0, 0, 100, 100);

    QGraphicsEllipseItem *cercleConicalGradient = new QGraphicsEllipseItem(0,0,100,100);
    QGraphicsRectItem *carreConicalGradient = new QGraphicsRectItem(0, 0, 100, 100);

    QGraphicsEllipseItem *cercleRadialGradient = new QGraphicsEllipseItem(0,0,100,100);

    QGraphicsEllipseItem *cercleTexture = new QGraphicsEllipseItem(0,0,100,100);

    // Init des variables brush
    QLinearGradient brushLinearGradient(20, 20, 100, 100);
    brushLinearGradient.setColorAt(0, Qt::white);
    brushLinearGradient.setColorAt(1, Qt::blue);

    QConicalGradient brushConicalGradient(25, 25, 0);
    brushConicalGradient.setColorAt(0, Qt::white);
    brushConicalGradient.setColorAt(1, Qt::blue);

    QRadialGradient brushRadialGradient(30, 30, 100);
    brushRadialGradient.setColorAt(0, Qt::white);
    brushRadialGradient.setColorAt(1, Qt::blue);

    QBrush brushTexture;//(Qt::TexturePattern);
    brushTexture.setTexture(QPixmap("/home/USERS/ELEVES/brique.jpg"));

    // On fait les différents brush
    cercleLinearGradient->setBrush(brushLinearGradient);
    carreLinearGradient->setBrush(brushLinearGradient);

    cercleConicalGradient->setBrush(brushConicalGradient);
    carreConicalGradient->setBrush(brushConicalGradient);

    cercleRadialGradient->setBrush(brushRadialGradient);

    cercleTexture->setBrush(brushTexture);

    // Ajouts des objets dans la scene
    scene->addItem(cercleLinearGradient);
    scene->addItem(carreLinearGradient);

    scene->addItem(cercleConicalGradient);
    scene->addItem(carreConicalGradient);

    scene->addItem(cercleRadialGradient);

    scene->addItem(cercleTexture);

    // Placement des objets sur la scene
    cercleLinearGradient->setPos(50, 50);
    carreLinearGradient->setPos(150, 50);

    cercleConicalGradient->setPos(250, 50);
    carreConicalGradient->setPos(50, 150);

    cercleRadialGradient->setPos(150, 150);

    cercleTexture->setPos(250, 150);
}

void Dessin::on_pushButtonFlocon_clicked()
{
    QPolygon unFlocon;
    unFlocon.setPoints(66,
                       302,8,
                       358,7,
                       355,117,
                       441,61,
                       463,105,
                       357,179,
                       357,322,
                       476,250,
                       488,128,
                       534,112,
                       533,215,
                       621,164,
                       655,214,
                       562,267,
                       653,312,
                       622,353,
                       508,300,
                       381,370,
                       508,442,
                       622,387,
                       651,429,
                       564,473,
                       656,526,
                       623,579,
                       533,527,
                       535,629,
                       489,614,
                       478,492,
                       357,421,
                       357,562,
                       464,632,
                       443,680,
                       357,625,
                       358,734,
                       302,734,
                       303,624,
                       216,678,
                       197,633,
                       304,561,
                       302,420,
                       182,493,
                       172,613,
                       124,628,
                       127,526,
                       36,578,
                       4,528,
                       97,474,
                       7,429,
                       35,388,
                       149,443,
                       279,371,
                       150,297,
                       35,352,
                       6,311,
                       96,268,
                       4,213,
                       36,162,
                       125,216,
                       124,113,
                       170,127,
                       182,250,
                       303,322,
                       303,179,
                       195,107,
                       216,62,
                       302,117);

    QGraphicsPolygonItem *flocon = new QGraphicsPolygonItem(unFlocon);

    scene->addItem(flocon);

    flocon->setScale(0.5);

    flocon->setPos(50,50);
}

