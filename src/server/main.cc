#include <QtCore/QCoreApplication>
#include "world.h"
#include "map.h"

#define DEFAULT_CENTRAL_SERVER_HOST "127.0.0.1"
#define DEFAULT_CENTRAL_SERVER_PORT 50000
#define DEFAULT_HOST QHostAddress::Any
#define DEFAULT_PORT 8799

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    World world(DEFAULT_HOST, DEFAULT_PORT);
    world.start(QHostAddress(DEFAULT_CENTRAL_SERVER_HOST), DEFAULT_CENTRAL_SERVER_PORT);
//Testing map generation algorithms:
//    Map map;
//    map.generateMap();
    return a.exec();
}
