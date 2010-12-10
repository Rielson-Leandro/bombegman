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
    if (m_pos != p) {
        m_pos = p;
        emit posChanged();
    }
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
