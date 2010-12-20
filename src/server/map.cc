#include "map.h"
#include "rand.h"
#include <QDebug>

#define MAX_MAP_WIDTH 16
#define MAX_MAP_HEIGHT 16

Map::Map(QObject *parent) :
    QObject(parent)
{
    Settings *settings = Settings::getInstance();

    /*Since it's flexible, we need to check if the user has set valid map parameters
      otherwise we won't start the server application:*/

    if (settings->width > MAX_MAP_WIDTH || settings->width < 5 ||
        settings->height > MAX_MAP_HEIGHT || settings->height < 5)
    {
        qWarning("WARNING: width and height parameters should be between 5 and 16. Setting to default.");
        m_width = settings->width < 5 ? 5 : 16;
        m_height = settings->height < 5 ? 5 : 16;
    } else {
        m_width = settings->width;
        m_height = settings->height;
    }

    if (settings->density > 10 | settings->density < 0)
    {
        qWarning("WARNING: density parameter should be between 0 and 10. Setting to default.");
        density = settings < 0 ? 0 : 10;
    } else {
        density = settings->density; //Bricks density in the map (randomly positioned)
    }

    if (settings->winterval < 2 || (settings->winterval > settings->width - 1 &&
        settings->winterval > settings->height - 1))
    {
        qWarning("WARNING: winterval parameter should be between 1 and the largest dimension - 1. Setting to default.");
        winterval = 2; //Space between pillars (wall blocks)
    } else {
        winterval = settings->winterval; //Space between pillars (wall blocks)
    }

    if ( settings->ini_winterval < 2 ||
        (settings->ini_winterval >= (settings->width / 2)) &&
        (settings->ini_winterval >= (settings->height / 2)))
    {
        qWarning("WARNING: ini_winterval parameter should be more than 2 and less than the half of the largest dimension. Setting to default.");
        ini_winterval = 2;
    } else {
        ini_winterval = settings->ini_winterval; //Where the pillars zone begins
    }

    if ( settings->finalx_winterval > (settings->width - 2) ||
         settings->finaly_winterval > (settings->height - 2) ||
         settings->finalx_winterval < settings->ini_winterval ||
         settings->finaly_winterval < settings->ini_winterval)
    {
        qWarning("WARNING: finalx_winterval and finaly_winterval parameters should be more than the ini_winterval parameter and less than the respective dimension. Setting to default.");
        finalx_winterval = ini_winterval + 1; //Where the pillars zone ends
        finaly_winterval = ini_winterval + 1; //Where the pillars zone ends
    } else {
        finalx_winterval = settings->finalx_winterval; //Where the pillars zone ends
        finaly_winterval = settings->finaly_winterval; //Where the pillars zone ends
    }

    /*End of map parameters check.*/
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
