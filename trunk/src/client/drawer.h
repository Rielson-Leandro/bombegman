#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include "mapentity.h"

class QGraphicsScene;

class Drawer : public QObject
{
Q_OBJECT
public:
    explicit Drawer(QGraphicsScene *scene, QObject *parent = 0);

public slots:
    void requestMovement(MapEntity entity, QPoint newPos);
    void requestNewEntity(MapEntity entity, QPoint pos);
    void requestHavoc(MapEntity entity);

private:
    QGraphicsScene *scene;
};

#endif // DRAWER_H
