#include <QtCore/QCoreApplication>
#include <QString>
#include "world.h"
#include "map.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Settings *settings = Settings::getInstance();
    QString central_server_host = settings->central_server_host;
    int central_server_port = settings->central_server_port;
    QString host = settings->host;
    int port = settings->port;

    World world(QHostAddress(host), port);
    world.start(QHostAddress(central_server_host), central_server_port);

    return a.exec();
}
