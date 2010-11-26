#include "formatter.h"

Formatter::Formatter(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    socket(socket)
{
}
