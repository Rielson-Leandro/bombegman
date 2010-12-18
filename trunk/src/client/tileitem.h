#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsObject>

class TileItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum State
    {
        EMPTY,
        BRICK,
        WALL
    };

    explicit TileItem(State state = EMPTY, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    State state() const;
    void setState(State s);

private:
    State m_state;
};

inline TileItem::State TileItem::state() const
{
    return m_state;
}

#endif // TILEITEM_H
