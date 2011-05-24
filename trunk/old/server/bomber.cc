#include "bomber.h"
#include "protocol.h"

Bomber::Bomber(World *parent) :
    MapEntity(parent)
{
}

char Bomber::getType()
{
    //In our protocol, a Bomber is seen as the player it belongs to.
    return PLAYER;
}
