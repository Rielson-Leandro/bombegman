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

    const Tile &getTile(int x, int y) const;
    Tile &getTile(int x, int y);

    void generateMap(/* parameters */);
    bool addMapEntity(MapEntity *entity, QPoint p);
    void removeEntity(MapEntity *entity);

    bool setPos(MapEntity *entity, QPoint p);

    QPoint getDimensions() const;

//    QPoint find(Tile::Space space, QPoint hint);
private:
    Tile tiles[16][16];
    int m_width;
    int m_height;

    int density;
    int winterval;
    int ini_winterval;
    int finalx_winterval;
    int finaly_winterval;
};

inline QPoint Map::getDimensions() const
{
    return QPoint(m_width, m_height);
}

#endif // MAP_H
