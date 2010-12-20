#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsObject>

class PlayerItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit PlayerItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    int dir;
    int state;
};

#endif // PLAYERITEM_H
