#include "qgraphicsballecollisionitem.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QtMath>

QGraphicsBalleCollisionItem::QGraphicsBalleCollisionItem(qreal x, qreal y, qreal width, qreal height, QGraphicsRectItem *_raquette, QGraphicsItem *parent):QGraphicsEllipseItem (x,y,width,height,parent),raquette(_raquette),dx(2),dy(2)
{

}

void QGraphicsBalleCollisionItem::advance(int step)
{
    moveBy(dx,dy);   // deplacement de dx pixel horizontalement
    qreal largeurBoule=rect().width();
    qreal largeurScene=scene()->width();
    qreal hauteurScene=scene()->height();

    // boule arrive sur bord gauche ou droit on inverse le sens horizontal
    if (x()<=qFabs(dx) || x()>=(largeurScene-largeurBoule))
    {
        dx=-dx;
    }
    // boule arrive sur bord haut ou bas on inverse le sens vertical
    if (y()<=qFabs(dy) || y()>=(hauteurScene-largeurBoule))
    {
        dy=-dy;
    }
    // gestion des collisions
    QList<QGraphicsItem*> listeDesObjetsEnCollisions=this->collidingItems();
    if (listeDesObjetsEnCollisions.count()>0)
    {
        foreach(QGraphicsItem *objet,listeDesObjetsEnCollisions)
        {
            // si l'objet n'est pas la raquette, le supprimer de la scene
            // et inverser la trajectoire de la balle
            if (objet!=raquette)
            {
                scene()->removeItem(objet);
                dx=-dx;
                dy=-dy;
            }
            else    // si c'est la raquette, changer le sens de la balle
            {
                dy=-dy;
            }
        }
    }
}
