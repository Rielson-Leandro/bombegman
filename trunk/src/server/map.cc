#include "map.h"
#include "rand.h"
#include <QDebug>

Map::Map(QObject *parent) :
    QObject(parent)
{
    Settings *settings = Settings::getInstance();
    this->density = settings->density; //Bricks density in the map (randomly positioned)
    this->winterval = settings->winterval; //Space between pillars (wall blocks)
    this->ini_winterval = settings->ini_winterval; //Where the pillars zone begins
    this->finalx_winterval = settings->finalx_winterval; //Where the pillars zone ends
    this->finaly_winterval = settings->finaly_winterval; //Where the pillars zone ends
    this->m_width = settings->width;
    this->m_height = settings->height;
}

const Map::Tile &Map::getTile(int x, int y) const
{
    return tiles[x][y];
}

/* The following method will generate the map according to the parameters set
in the configuration file. Basically it will set the borders, bases, pillars
and randomly fill the entery maps with bricks or empty spaces. The amount of
bricks will depend on the density parameter. */
void Map::generateMap()
{
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            //Borders
            if(i == 0 || i == m_width - 1 || j == 0 || j == m_height - 1)
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
    for(int i = ini_winterval; i <= finalx_winterval; i += winterval)
    {
        for(int j = ini_winterval; j <= finaly_winterval; j += winterval)
        {
            tiles[i][j].space = Tile::WALL;
        }

    }

    //Drawing bombers spawn bases(L):
    tiles[1][1].space = Tile::EMPTY;
    tiles[1][2].space = Tile::EMPTY;
    tiles[2][1].space = Tile::EMPTY;

    tiles[1][m_height - 3].space = Tile::EMPTY;
    tiles[1][m_height - 2].space = Tile::EMPTY;
    tiles[2][m_height - 2].space = Tile::EMPTY;

    tiles[m_width - 3][1].space = Tile::EMPTY;
    tiles[m_width - 2][1].space = Tile::EMPTY;
    tiles[m_width - 2][2].space = Tile::EMPTY;

    tiles[m_width - 2][m_height - 3].space = Tile::EMPTY;
    tiles[m_width - 2][m_height - 2].space = Tile::EMPTY;
    tiles[m_width - 3][m_height - 2].space = Tile::EMPTY;
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
//    for (int i = hint.x();i < width;++i) {
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
