#include "drawer.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "tileitem.h"

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
    // TODO
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