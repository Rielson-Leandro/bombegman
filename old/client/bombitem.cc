#include "bombitem.h"
#include <QPainter>

enum State
{
    ALIVE
};

static const QImage *spritesset[] =
{
    NULL,
    NULL,
    NULL
};

BombItem::BombItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    state(0)
{
    if (!spritesset[0]) {
        spritesset[0] = new QImage(":/gfx/bomb1.png");
        spritesset[1] = new QImage(":/gfx/bomb2.png");
        spritesset[2] = new QImage(":/gfx/bomb3.png");
    }
    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer.start(250);
}

QRectF BombItem::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void BombItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, 0, *spritesset[state % 3]);
}

void BombItem::onTimeout()
{
    ++state;
    update();
}
