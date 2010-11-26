#include <QtCore/QCoreApplication>
#include "world.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSettings conf("server.ini",QSettings::IniFormat);
    int port = conf.value("port", 59000).toInt();
    World world;
    world.listen(QHostAddress::Any, port);

    return a.exec();
}
