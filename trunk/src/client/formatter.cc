#include "formatter.h"
#include <QTcpSocket>

#include "protocol.h"

Formatter::Formatter(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    socket(socket)
{
}

void Formatter::requestMovement(MapEntity entity, QPoint newPos)
{
    const char buffer[4] = {MOVEMENT,
                            entity.type,
                            entity.id,
                            MapEntity::getByte(newPos)};
    socket->write(buffer, 4);
}

void Formatter::requestInput(char type)
{
    char msg[3] = {INPUT, '\0', '\0'};
    msg[1] = type;
    socket->write(msg);
}
