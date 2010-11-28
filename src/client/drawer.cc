#include "drawer.h"
#include <QGraphicsScene>

Drawer::Drawer(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
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
