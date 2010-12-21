#include "bomb.h"
#include "protocol.h"
#include "player.h"

Bomb::Bomb(World *parent) :
    MapEntity(parent)
{
    range = 2;
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer.start(3000);
}

void Bomb::explode()
{
    if(!exploded){
        world()->onDestructionRequested(pos(), range);
        if(ownerPlayer)
        {
            ownerPlayer->decreaseActiveBombs();
        }
        exploded = true;
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
