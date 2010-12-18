#include "map.h"
#include "rand.h"
#include <QDebug>
#include <iostream>


Map::Map(QObject *parent) :
    QObject(parent)
{
    this->settings = Settings::getInstance();
    this->density = settings->density; //Bricks density in the map (randomly positioned)
    this->winterval = settings->winterval; //Space between pillars (wall blocks)
    this->ini_winterval = settings->ini_winterval; //Where the pillars zone begins
    this->final_winterval = settings->final_winterval; //Where the pillars zone ends
}

/* The following method will generate the map according to the parameters set
in the configuration file. Basically it will set the borders, bases, pillars
and randomly fill the entery maps with bricks or empty spaces. The amount of
bricks will depend on the density parameter. */

void Map::generateMap()
{


    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            //Borders
            if(i == 0 || i == 14 || j == 0 || j ==14)
            {
                tiles[i][j].space = Tile::WALL;
            }
            else
            {
                tiles[i][j].space = Tile::EMPTY;
            }
            //Randomly placing bricks:
            if(tiles[i][j].space != Tile::WALL && aleat(1,10) <= density){
                tiles[i][j].space = Tile::BRICK;
            }
        }
    }

    //Inserting pillars:
    for(int i = ini_winterval; i <= final_winterval; i += winterval)
    {
        for(int j = ini_winterval; j <= final_winterval; j += winterval)
        {
            tiles[i][j].space = Tile::WALL;
        }

    }

    //Drawing bombers spawn bases(L):
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

//    for(int i = 0; i < 15; i++)
//    {
//        for(int j = 0; j < 15; j++)
//        {
//            std::cout << tiles[i][j].space;
//        }
//        std::cout << std::endl;
//    }
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

    if (entity->pos() == p)
        return false;

    if (this->tiles[p.x()][p.y()].space != Tile::EMPTY)
    {
        return false;
    }

    foreach (MapEntity *e, this->tiles[p.x()][p.y()].entities){
        if(e->obstructive())
        {
            return false;
        }
    }

    tiles[entity->pos().x()][entity->pos().y()].entities.removeOne(entity);
    tiles[p.x()][p.y()].entities.append(entity);
    entity->setPos(p);
    qDebug() << entity->pos();
    return true;
}
