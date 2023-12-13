#ifndef QGRAPHICSBOULEHORIZONTALITEM_H
#define QGRAPHICSBOULEHORIZONTALITEM_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>

class QGraphicsBouleHorizontalItem : public QGraphicsEllipseItem
{
public:
    QGraphicsBouleHorizontalItem(qreal x,
                                 qreal y,
                                 qreal width,
                                 qreal height,
                                 QGraphicsItem *parent = nullptr);

protected:
    void advance(int step) override;

private:

    qreal dx;

    QMediaPlayer player;
    QAudioOutput sortieAudio;
};

#endif // QGRAPHICSBOULEHORIZONTALITEM_H
