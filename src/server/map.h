#ifndef MAP_H
#define MAP_H

#include "mapentity.h"
#include <QObject>
#include <iostream>

class Map : public QObject
{
Q_OBJECT
public:
    struct Tile
    {
        enum Space
        {
            EMPTY,
            BRICK,
            WALL
        } space;
        QList<MapEntity *> entities;
    };

    explicit Map(QObject *parent = 0);

    void generateMap(/* parameters */);
    bool addMapEntity(MapEntity *entity, QPoint p);
    void removeEntity(MapEntity *entity);

    bool setPos(MapEntity *entity, QPoint p);

//    QPoint find(Tile::Space space, QPoint hint);
private:
    Tile tiles[16][16];
};

#endif // MAP_H
