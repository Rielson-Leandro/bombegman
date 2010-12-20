#include "bomb.h"

Bomb::Bomb(World *parent) :
    MapEntity(parent)
{
    range = 1;
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

void Bomb::onTimeOut(){
    explode();
}
