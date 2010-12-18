#include "map.h"
#include "rand.h"
#include <QDebug>

#define DENSITY         8   //Bricks density in the map (randomly positioned)
#define WINTERVAL        2   //Space between  (wall blocks)
#define INI_WINTERVAL    2   //Where the columns zone begins
#define FINAL_WINTERVAL  12  //Where the columns zone ends


Map::Map(QObject *parent) :
    QObject(parent)
{
}

/* The following method will generate the map according to the parameters set
in the configuration file. Basically it will set the borders, bases, pillars
and randomly fill the entery maps with bricks or empty spaces. The amount of
bricks will depend on the DENSITY parameter. */

void Map::generateMap()
{


    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            //Bordas
            if(i == 0 || i == 14 || j == 0 || j ==14)
            {
                tiles[i][j].space = Tile::WALL;
            }
            else
            {
                tiles[i][j].space = Tile::EMPTY;
            }
            //Sorteando os tijolos:
            if(tiles[i][j].space != Tile::WALL && aleat(1,10) <= DENSITY){
                tiles[i][j].space = Tile::BRICK;
            }
        }
    }

    //Inseririndo pilastras:
    for(int i = INI_WINTERVAL; i <= FINAL_WINTERVAL; i += WINTERVAL)
    {
        for(int j = INI_WINTERVAL; j <= FINAL_WINTERVAL; j += WINTERVAL)
        {
            tiles[i][j].space = Tile::WALL;
        }

    }

    //Bases onde os bombers nascem (L):
    tiles[1][1].space = Tile::EMPTY;
    tiles[1][2].space = Tile::EMPTY;
    tiles[2][1].space = Tile::EMPTY;
    tiles[3][1].space = Tile::EMPTY;

    tiles[1][11].space = Tile::EMPTY;
    tiles[1][12].space = Tile::EMPTY;
    tiles[1][13].space = Tile::EMPTY;
    tiles[2][13].space = Tile::EMPTY;

    tiles[12][1].space = Tile::EMPTY;
    tiles[13][1].space = Tile::EMPTY;
    tiles[13][2].space = Tile::EMPTY;
    tiles[13][3].space = Tile::EMPTY;

    tiles[13][12].space = Tile::EMPTY;
    tiles[13][13].space = Tile::EMPTY;
    tiles[12][13].space = Tile::EMPTY;
    tiles[11][13].space = Tile::EMPTY;

    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            qDebug() << tiles[i][j].space;
        }

    }
}

bool Map::addMapEntity(MapEntity *entity, QPoint p)
{
    tiles[p.x()][p.y()].entities.append(entity);
    entity->setPos(p);
    return true;
}

void Map::removeEntity(MapEntity *entity)
{
    tiles[entity->pos().x()][entity->pos().y()].entities.removeOne(entity);
}

//QPoint Map::find(Tile::Space space, QPoint hint)
//{
//    for (int i = hint.x();i < 16;++i) {
//        for (int j = 0;j < hint.y();++j) {
//            if (tiles[i][j].space == space)
//                return QPoint(i, j);
//        }
//    }
//    for (int i = )
//    return QPoint(-1, -1);
//}

bool Map::setPos(MapEntity *entity, QPoint p){
    //TODO check if it can be moved to the required position.

    if (entity->pos() == p)
        return false;

    tiles[entity->pos().x()][entity->pos().y()].entities.removeOne(entity);
    tiles[p.x()][p.y()].entities.append(entity);
    entity->setPos(p);
    qDebug() << entity->pos();
    return true;
}
