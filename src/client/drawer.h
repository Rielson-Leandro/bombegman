#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include <QHash>
#include "mapentity.h"

class QGraphicsScene;
class QGraphicsItem;
class QPushButton;
class QGraphicsProxyWidget;

class Drawer : public QObject
{
Q_OBJECT
public:
    explicit Drawer(QGraphicsScene *scene, QObject *parent = 0);
    ~Drawer();

signals:
    void removeButtonClicked();

public slots:
    void prepareMap(QPoint, char map[16][]);

    void requestMovement(MapEntity entity, QPoint newPos);
    void requestNewEntity(MapEntity entity, QPoint pos);
    void requestHavoc(MapEntity entity);

    void addReadyButton();
    void removeReadyButton();

private:
    QGraphicsScene *scene;
    QGraphicsItem *map[16][16];
    QHash<int, QGraphicsItem *> entities;

    bool sceneHasReadyButton;
    QPushButton *button;
    QGraphicsProxyWidget *buttonItem;
};

#endif // DRAWER_H
