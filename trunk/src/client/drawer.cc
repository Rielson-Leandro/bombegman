#include "drawer.h"
#include <QGraphicsScene>

Drawer::Drawer(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
}
