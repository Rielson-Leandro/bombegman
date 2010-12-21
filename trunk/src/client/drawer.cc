#include "drawer.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "protocol.h"
#include "tileitem.h"
#include "playeritem.h"
#include "bombitem.h"

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

void Drawer::requestMovement(MapEntity entity, QPoint newPos)
{
    // TODO
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

void Drawer::requestHavoc(MapEntity entity)
{
    // TODO
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
