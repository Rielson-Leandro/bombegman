#ifndef PROTOCOL_H
#define PROTOCOL_H

enum Action
{
    MOVEMENT   = 'M',
    NEW_ENTITY = 'N',
    DESTROYED  = 'D'
};

enum Entity
{
    PLAYER = 'P',
    BOMB   = 'B',
    BLOCK  = 'T',
    ITEM   = 'I'
};

enum Direction
{
    EAST  = 'E',
    NORTH = 'N',
    SOUTH = 'S',
    WEST  = 'W'
};

#endif // PROTOCOL_H
