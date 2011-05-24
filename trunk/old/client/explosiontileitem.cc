#include "explosiontileitem.h"
#include <QPainter>
#include <QTimer>
#include <QGraphicsScene>

static const QImage *spritesset[7] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

ExplosionTileItem::ExplosionTileItem(Type type, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    type(type)
{
    if (!spritesset[0]) {
        spritesset[0] = new QImage(":/gfx/expc.png");
        spritesset[1] = new QImage(":/gfx/expn.png");
        spritesset[2] = new QImage(":/gfx/expe.png");
        spritesset[3] = new QImage(":/gfx/exps.png");
        spritesset[4] = new QImage(":/gfx/expw.png");
        spritesset[5] = new QImage(":/gfx/expv.png");
        spritesset[6] = new QImage(":/gfx/exph.png");
    }
    QTimer::singleShot(200, this, SLOT(onTimeout()));
}

QRectF ExplosionTileItem::boundingRect() const
{
    return QRectF(0., 0., 32., 32.);
}

void ExplosionTileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, 0, *spritesset[type]);
}

void ExplosionTileItem::onTimeout()
{
    scene()->removeItem(this);
    deleteLater();
}
