#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include <QMap>
#include "mapentity.h"
#include <QHostAddress>

class World;
class QGraphicsScene;
class QGraphicsObject;
class QPushButton;
class QGraphicsProxyWidget;
class TileItem;

class Drawer : public QObject
{
Q_OBJECT
public:
    explicit Drawer(World *world, QGraphicsScene *scene, QObject *parent = 0);
    ~Drawer();

signals:
    void matchRequested();

public slots:
    void prepareMap(const QPoint dimensions, char map[16][16]);
    void drawMainMenu();

    void requestMovement(MapEntity entity, char dir);
    void requestNewEntity(MapEntity entity, QPoint pos);
    void requestEntityDestroyed(MapEntity entity);
    void requestExplosion(QPoint center, int northRange, int eastRange,
                          int southRange, int westRange);

private slots:
    void onConnectionRequested(const QHostAddress &address, quint16 port);
    void onMatchRequested();

private:
    World *world;
    QGraphicsScene *scene;
    QGraphicsProxyWidget *connectionDialogItem;
    QGraphicsObject *map[16][16];
    QMap<int, QGraphicsObject *> entities;
    TileItem *tiles[16][16];

    bool sceneHasReadyButton;
    QPushButton *button;
    QGraphicsProxyWidget *buttonItem;
};

#endif // DRAWER_H
