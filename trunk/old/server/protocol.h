#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QPoint>

enum Entity
{
    PLAYER = 'P',
    BOMB   = 'B',
    TILE   = 'T',
    ITEM   = 'I'
};

enum Action
{
    MOVEMENT   = 'M',
    NEW_ENTITY = 'N',
    DESTROYED  = 'D',
    INPUT      = 'I',
    REQUEST    = 'R',
    EXPLOSION  = 'E'
};

enum Input
{
    BOMB_KEY_PRESS   = '0',
    BOMB_KEY_RELEASE = '1'
};

enum Direction
{
    EAST  = 'E',
    NORTH = 'N',
    SOUTH = 'S',
    WEST  = 'W'
};

enum
{
    MATCH = 'M'
};

inline QPoint getPos(unsigned char byte)
{
    const int x = (byte & 0xF0) >> 4;
    const int y = byte & 0x0F;
    return QPoint(x, y);
}

inline unsigned char getByte(QPoint point)
{
    const unsigned char x = point.x(), y = point.y();
    unsigned char byte = x << 4;
    byte |= y;
    return byte;
}

#endif // PROTOCOL_H
