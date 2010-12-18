#ifndef MAPENTITY_H
#define MAPENTITY_H

#include <QPoint>

struct MapEntity
{
    char type;
    unsigned char id;

    MapEntity(char type, unsigned char id) : type(type), id(id) {}
    MapEntity() : type(0), id(0) {}

    QPoint getPos() const
    {
        return getPos(id);
    }

    static QPoint getPos(unsigned char byte)
    {
        const int x = (byte & 0xF0) >> 4;
        const int y = byte & 0x0F;
        return QPoint(x, y);
    }

    static unsigned char getByte(QPoint point)
    {
        const unsigned char x = point.x(), y = point.y();
        unsigned char byte = x << 4;
        byte |= y;
        return byte;
    }
};

#endif // MAPENTITY_H
