#include "world.h"


World::World(QObject *parent) :
        QObject(parent)
{


}

void World::listen(QHostAddress hostAddress, quint16 port){
    server->listen(hostAddress, port);
}


