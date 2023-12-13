#ifndef QGRAPHICSBALLECOLLISIONITEM_H
#define QGRAPHICSBALLECOLLISIONITEM_H

#include <QObject>
#include <QWidget>
#include <QGraphicsEllipseItem>

class QGraphicsBalleCollisionItem : public QGraphicsEllipseItem
{
public:
    QGraphicsBalleCollisionItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
protected:
    void advance(int step) override;
private:
    QGraphicsRectItem *raquette;
    qreal dx;
    qreal dy;
};

#endif // QGRAPHICSBALLECOLLISIONITEM_H
