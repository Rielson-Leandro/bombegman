#include "drawer.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "protocol.h"
#include "tileitem.h"
#include "playeritem.h"
#include "bombitem.h"
#include "explosiontileitem.h"
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QDebug>

Drawer::Drawer(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    sceneHasReadyButton(false),
    button(new QPushButton("READY")),
    buttonItem(new QGraphicsProxyWidget)
{
    buttonItem->setWidget(button);
    connect(button, SIGNAL(clicked()), this, SIGNAL(removeButtonClicked()));
}

Drawer::~Drawer()
{
    if (sceneHasReadyButton)
        scene->removeItem(buttonItem);
    delete button;
    delete buttonItem;
}

void Drawer::prepareMap(const QPoint dimensions, char map[16][16])
{
    for (int i = 0;i < dimensions.x();++i) {
        for (int j = 0;j < dimensions.y();++j) {
            TileItem *item = new TileItem(static_cast<TileItem::State>(map[i][j]));
            tiles[i][j] = item;
            item->setPos(32. * i, 32. * j);
            scene->addItem(item);
        }
    }
}

void Drawer::requestMovement(MapEntity entity, char dir)
{
    QGraphicsObject *item = entities.value(entity.id, NULL);
    if (item) {
        QPointF p = item->pos();
        switch (dir) {
        case NORTH:
            p.ry() -= 32.;
            break;
        case EAST:
            p.rx() += 32.;
            break;
        case SOUTH:
            p.ry() += 32.;
            break;
        case WEST:
            p.rx() -= 32.;
        }

        QPropertyAnimation *animation = new QPropertyAnimation(item, "pos", this);
        animation->setEndValue(p);
        animation->setDuration(200);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        {
            PlayerItem *playerItem = dynamic_cast<PlayerItem *>(item);
            if (playerItem) {
                playerItem->setDir(dir);
                playerItem->startAnimated();
                connect(animation, SIGNAL(finished()), playerItem, SLOT(stopAnimated()));
            }
        }
    }
}

void Drawer::requestNewEntity(MapEntity entity, QPoint pos)
{
    switch (entity.type) {
    case PLAYER:
        {
            PlayerItem *item = new PlayerItem;
            entities[entity.id] = item;
            item->setPos(32. * pos.x(), 32. * pos.y());
            item->setZValue(2.);
            scene->addItem(item);
            break;
        }
    case BOMB:
        {
            BombItem *item = new BombItem;
            entities[entity.id] = item;
            item->setPos(32. * pos.x(), 32. * pos.y());
            item->setZValue(1.);
            scene->addItem(item);
            break;
        }
        break;
    case ITEM:
        ;// TODO
    }
}

void Drawer::requestEntityDestroyed(MapEntity entity)
{
    if (entity.type == TILE) {
        QPoint p = entity.getPos();
        TileItem *item = tiles[p.x()][p.y()];
        item->setState(TileItem::EMPTY);
    } else {
        QGraphicsObject *item = entities.value(entity.id, NULL);
        scene->removeItem(item);
        delete item;
    }
}

void Drawer::requestExplosion(QPoint center, int northRange, int eastRange,
                              int southRange, int westRange)
{
    QGraphicsItem *item = new ExplosionTileItem(ExplosionTileItem::CENTER);
    item->setPos(center.x() * 32, center.y() * 32);
    scene->addItem(item);

    --northRange;
    for (int i = 1;i < northRange;++i) {
        item = new ExplosionTileItem(ExplosionTileItem::VERTICAL);
        item->setPos(center.x() * 32, (center.y() - i) * 32);
        item->setZValue(.5);
        scene->addItem(item);
    }
    if (northRange) {
        item = new ExplosionTileItem(ExplosionTileItem::NORTH);
        item->setPos(center.x() * 32, (center.y() - northRange) * 32);
        item->setZValue(.5);
        scene->addItem(item);
    }

    --eastRange;
    for (int i = 1;i < eastRange;++i) {
        item = new ExplosionTileItem(ExplosionTileItem::HORIZONTAL);
        item->setPos((center.x() + i) * 32, center.y() * 32);
        item->setZValue(.5);
        scene->addItem(item);
    }
    if (eastRange) {
        item = new ExplosionTileItem(ExplosionTileItem::EAST);
        item->setPos((center.x() + eastRange) * 32, center.y() * 32);
        item->setZValue(.5);
        scene->addItem(item);
    }

    --southRange;
    for (int i = 1;i < southRange;++i) {
        item = new ExplosionTileItem(ExplosionTileItem::VERTICAL);
        item->setPos(center.x() * 32, (center.y() + i) * 32);
        item->setZValue(.5);
        scene->addItem(item);
    }
    if (southRange) {
        item = new ExplosionTileItem(ExplosionTileItem::SOUTH);
        item->setPos(center.x() * 32, (center.y() + southRange) * 32);
        item->setZValue(.5);
        scene->addItem(item);
    }

    --westRange;
    for (int i = 1;i < westRange;++i) {
        item = new ExplosionTileItem(ExplosionTileItem::HORIZONTAL);
        item->setPos((center.x() - i) * 32, center.y() * 32);
        item->setZValue(.5);
        scene->addItem(item);
    }
    if (westRange) {
        item = new ExplosionTileItem(ExplosionTileItem::WEST);
        item->setPos((center.x() - westRange) * 32, center.y() * 32);
        item->setZValue(.5);
        scene->addItem(item);
    }
}

void Drawer::addReadyButton()
{
    if (!sceneHasReadyButton) {
        scene->addItem(buttonItem);
        sceneHasReadyButton = true;
    }
}

void Drawer::removeReadyButton()
{
    if (sceneHasReadyButton) {
        scene->removeItem(buttonItem);
        sceneHasReadyButton = false;
    }
}
