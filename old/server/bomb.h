#ifndef BOMB_H
#define BOMB_H

#include "mapentity.h"
#include "world.h"
#include <QTimer>

class Player;

class Bomb : public MapEntity
{
Q_OBJECT
public:
    explicit Bomb(World *world, Player *player = NULL);
    void explode();
    char getType();
    ~Bomb();

private slots:
    void onTimeOut();

private:
    Player *owner;
    volatile bool exploded;
    int range;
    QTimer timer;
};

#endif // BOMB_H

