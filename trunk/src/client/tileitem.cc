#include "tileitem.h"
#include <QPainter>

static const QImage tiles[] =
{
    QImage(":/gfx/empty.png"),
    QImage(":/gfx/brick.png"),
    QImage(":/gfx/wall.png")
};

TileItem::TileItem(State state, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_state(state)
{
}

QRectF TileItem::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void TileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, 0, tiles[m_state]);
}

void TileItem::setState(State s)
{
    if (m_state != s) {
        m_state = s;
        update();
    }
}
