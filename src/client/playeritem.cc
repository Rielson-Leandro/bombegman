#include "playeritem.h"
#include <QPainter>

enum Dir
{
    EAST,
    NORTH,
    SOUTH,
    WEST
};

static const QImage *spritesset[] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

PlayerItem::PlayerItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    dir(SOUTH),
    state(0)
{
    if (!spritesset[0]) {
        spritesset[0] = new QImage(":/gfx/bombere0");
        spritesset[1] = new QImage(":/gfx/bombere1");
        spritesset[2] = new QImage(":/gfx/bombere2");
        spritesset[3] = new QImage(":/gfx/bombern0");
        spritesset[4] = new QImage(":/gfx/bombern1");
        spritesset[5] = new QImage(":/gfx/bombern2");
        spritesset[6] = new QImage(":/gfx/bombers0");
        spritesset[7] = new QImage(":/gfx/bombers1");
        spritesset[8] = new QImage(":/gfx/bombers2");
        spritesset[9] = new QImage(":/gfx/bomberw0");
        spritesset[10] = new QImage(":/gfx/bomberw1");
        spritesset[11] = new QImage(":/gfx/bomberw2");
    }
}

QRectF PlayerItem::boundingRect() const
{
    return QRectF(0, -32, 32, 64);
}

void PlayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, -32, *spritesset[dir * 3 + state]);
}
