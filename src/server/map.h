#ifndef MAP_H
#define MAP_H

#include "mapentity.h"
#include "settings.h"
#include <QObject>

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
    Settings *settings;
    int density;
    int winterval;
    int ini_winterval;
    int final_winterval;
};

#endif // MAP_H
