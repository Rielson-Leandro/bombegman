#include "bomb.h"
#include "protocol.h"

Bomb::Bomb(World *parent) :
    MapEntity(parent)
{
    range = 2;
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer.start();

}

void Bomb::explode()
{
    if(!exploded){
        world()->onDestructionRequested(pos(), range);
        ownerPlayer->decreaseActiveBombs();
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
