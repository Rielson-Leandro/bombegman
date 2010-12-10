#include <QtCore/QCoreApplication>
#include "server.h"

#define DEFAULT_HOST_ADDRESS QHostAddress::Any
#define DEFAULT_PORT 50000

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server s;
    s.listen(QHostAddress(DEFAULT_HOST_ADDRESS), DEFAULT_PORT);

    return a.exec();
}
