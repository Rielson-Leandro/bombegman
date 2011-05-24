#ifndef PROTOCOL_H
#define PROTOCOL_H

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

#endif // PROTOCOL_H
