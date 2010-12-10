#ifndef BOMBER_H
#define BOMBER_H

#include "mapentity.h"

class Bomber : public MapEntity
{
Q_OBJECT
public:
    explicit Bomber(World *parent = 0);

signals:

public slots:

};

#endif // BOMBER_H
