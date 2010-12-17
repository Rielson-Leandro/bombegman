#include "drawer.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>

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

void Drawer::prepareMap(QPoint, char map[15][15])
{
    // TODO
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
