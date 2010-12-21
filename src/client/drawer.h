#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include <QMap>
#include "mapentity.h"

class QGraphicsScene;
class QGraphicsObject;
class QPushButton;
class QGraphicsProxyWidget;
class TileItem;

class Drawer : public QObject
{
Q_OBJECT
public:
    explicit Drawer(QGraphicsScene *scene, QObject *parent = 0);
    ~Drawer();

signals:
    void removeButtonClicked();

public slots:
    void prepareMap(const QPoint dimensions, char map[16][16]);

    void requestMovement(MapEntity entity, char dir);
    void requestNewEntity(MapEntity entity, QPoint pos);
    void requestHavoc(MapEntity entity);

    void addReadyButton();
    void removeReadyButton();

private:
    QGraphicsScene *scene;
    QGraphicsObject *map[16][16];
    QMap<int, QGraphicsObject *> entities;
    TileItem *tiles[16][16];

    bool sceneHasReadyButton;
    QPushButton *button;
    QGraphicsProxyWidget *buttonItem;
};

#endif // DRAWER_H
