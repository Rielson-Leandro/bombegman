#ifndef BOMB_H
#define BOMB_H

#include "mapentity.h"

class Bomb : public MapEntity
{
Q_OBJECT
public:
    explicit Bomb(World *parent = 0);

signals:

public slots:

};

#endif // BOMB_H
