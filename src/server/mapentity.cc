#include "mapentity.h"
#include "world.h"

static quint8 count = 0;

MapEntity::MapEntity(World *parent) :
    QObject(parent),
    m_world(parent)
{
    id = count++;
}

void MapEntity::setPos(const QPoint &p)
{
    m_pos = p;
}

void MapEntity::explode()
{
}

bool MapEntity::obstrutive() const
{
    return false;
}

quint8 MapEntity::getId() const
{
    return id;
}

World *MapEntity::world()
{
    return m_world;
}
