#include "playeritem.h"
#include <QPainter>

enum Dir
{
    EAST,
    NORTH,
    SOUTH,
    WEST
};

static const QImage spritesset[] =
{
    QImage(":/gfx/bombere0"),
    QImage(":/gfx/bombere1"),
    QImage(":/gfx/bombere2"),
    QImage(":/gfx/bombern0"),
    QImage(":/gfx/bombern1"),
    QImage(":/gfx/bombern2"),
    QImage(":/gfx/bombers0"),
    QImage(":/gfx/bombers1"),
    QImage(":/gfx/bombers2"),
    QImage(":/gfx/bomberw0"),
    QImage(":/gfx/bomberw1"),
    QImage(":/gfx/bomberw2")
};

PlayerItem::PlayerItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    dir(SOUTH),
    state(0)
{
}

QRectF PlayerItem::boundingRect() const
{
    return QRectF(0, -32, 32, 64);
}

void PlayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, -32, spritesset[dir * 3 + state]);
}
