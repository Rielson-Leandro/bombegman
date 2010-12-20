#ifndef BOMB_H
#define BOMB_H

#include "mapentity.h"
#include "player.h"
#include "world.h"
#include <QTimer>

class Bomb : public MapEntity
{
Q_OBJECT
private:
    Player *ownerPlayer;
    bool exploded;
    int range;
    QTimer timer;
public:
    explicit Bomb(World *parent = 0);
    void explode();
    char getType();

signals:

private slots:
    void onTimeOut();
};

#endif // BOMB_H
