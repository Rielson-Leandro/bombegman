#include <QtCore/QCoreApplication>
#include "world.h"

#define DEFAULT_CENTRAL_SERVER_HOST "192.168.0.114"
#define DEFAULT_CENTRAL_SERVER_PORT 50000
#define DEFAULT_HOST QHostAddress::Any
#define DEFAULT_PORT 8799

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    World world(DEFAULT_HOST, DEFAULT_PORT);
    world.start(QHostAddress(DEFAULT_CENTRAL_SERVER_HOST), DEFAULT_CENTRAL_SERVER_PORT);

    return a.exec();
}
