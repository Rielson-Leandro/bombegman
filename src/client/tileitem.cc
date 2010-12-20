#include "tileitem.h"
#include <QPainter>

static const QImage *tiles[] =
{
    NULL,
    NULL,
    NULL
};

TileItem::TileItem(State state, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_state(state)
{
    if (!tiles[0]) {
        tiles[0] = new QImage(":/gfx/empty.png");
        tiles[1] = new QImage(":/gfx/brick.png");
        tiles[2] = new QImage(":/gfx/wall.png");
    }
}

QRectF TileItem::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void TileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, 0, *tiles[m_state]);
}

void TileItem::setState(State s)
{
    if (m_state != s) {
        m_state = s;
        update();
    }
}
