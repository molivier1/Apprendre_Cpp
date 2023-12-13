#include "qgraphicsboulehorizontalitem.h"

QGraphicsBouleHorizontalItem::QGraphicsBouleHorizontalItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    :QGraphicsEllipseItem(x,y,width,height, parent), dx(2)
{
    player.setAudioOutput(&sortieAudio);
    player.setSource(QUrl::fromLocalFile("/home/mateo/Documents/SNIR_2/Code/Apprendre_Cpp/Cours/Multimedia/Son/Decouverte_son/SIRSALOPARD_1.mp3"));
    sortieAudio.setVolume(50);
}

void QGraphicsBouleHorizontalItem::advance(int step)
{
    moveBy(dx, 0);
    qreal largeurBoule=rect().width();
    qreal largeurScene=scene()->width();

    if(x()<=2)
    {
        dx=2;
    }

    if(x()>=(largeurScene-largeurBoule))
    {
        dx =-2;
        player.play();
    }
}
