#include "mapobject.h"

MapObject::MapObject(QObject *parent) :
    QObject(parent)
{
}

void MapObject::setPos(const QPoint &p)
{
    if (m_pos != p) {
        m_pos = p;
        emit posChanged();
    }
}

void MapObject::explode()
{
}

bool MapObject::obstrutive() const
{
    return false;
}
