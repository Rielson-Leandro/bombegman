#include "map.h"
#include "rand.h"


#define DENSITY 8


Map::Map(QObject *parent) :
    QObject(parent)
{
}


void Map::generateMap()
{

    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            //Bordas
            if(i == 0 || i == 15 || j == 0 || j ==15)
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

    //Bases onde os bombers nascem (L):
    tiles[1][1].space = Tile::EMPTY;
    tiles[1][2].space = Tile::EMPTY;
    tiles[2][1].space = Tile::EMPTY;
    tiles[3][1].space = Tile::EMPTY;

    tiles[1][14].space = Tile::EMPTY;
    tiles[1][13].space = Tile::EMPTY;
    tiles[1][12].space = Tile::EMPTY;
    tiles[2][14].space = Tile::EMPTY;

    tiles[14][1].space = Tile::EMPTY;
    tiles[13][1].space = Tile::EMPTY;
    tiles[12][1].space = Tile::EMPTY;
    tiles[14][2].space = Tile::EMPTY;

    tiles[14][14].space = Tile::EMPTY;
    tiles[13][14].space = Tile::EMPTY;
    tiles[14][12].space = Tile::EMPTY;
    tiles[14][13].space = Tile::EMPTY;

    // TODO: inserir pilastras
}

bool Map::addMapEntity(MapEntity *entity, QPoint p)
{
    tiles[p.x()][p.y()].entities.append(entity);
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
