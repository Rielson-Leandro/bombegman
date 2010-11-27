#include "mapentity.h"

MapEntity::MapEntity(QObject *parent) :
    QObject(parent)
{
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
