#include "bomb.h"
#include "protocol.h"
#include "player.h"

Bomb::Bomb(World *world, Player *player) :
    MapEntity(world),
    owner(player),
    exploded(false),
    range(2)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer.start(3000);
    timer.setSingleShot(true);
}

void Bomb::explode()
{
    if(!exploded){
        exploded = true;
        disconnect(&timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
        world()->requestExplosion(pos(), range);
        if(owner)
        {
            owner->decreaseActiveBombs();
        }
    }
}

void Bomb::onTimeOut()
{
    explode();
}

char Bomb::getType()
{
    return BOMB;
}


Bomb::~Bomb()
{
}

