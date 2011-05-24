#include "formatter.h"
#include <QTcpSocket>

#include "protocol.h"

Formatter::Formatter(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    socket(socket)
{
}

void Formatter::requestMovement(char dir)
{
    const char buffer[2] = {MOVEMENT, dir};
    socket->write(buffer, 2);
}

void Formatter::requestInput(char type)
{
    char buffer[2] = {INPUT, type};
    socket->write(buffer, 2);
}

void Formatter::requestMatch()
{
    static const char buffer[2] = {REQUEST, MATCH};
    socket->write(buffer, 2);
}
