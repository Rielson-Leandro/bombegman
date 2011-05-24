#ifndef EXPLOSIONTILEITEM_H
#define EXPLOSIONTILEITEM_H

#include <QGraphicsObject>

class ExplosionTileItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum Type
    {
        CENTER,
        NORTH,
        EAST,
        SOUTH,
        WEST,
        VERTICAL,
        HORIZONTAL
    };

    explicit ExplosionTileItem(Type type, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private slots:
    void onTimeout();

private:
    Type type;
};

#endif // EXPLOSIONTILEITEM_H
