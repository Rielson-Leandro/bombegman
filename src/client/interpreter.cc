#include "interpreter.h"
#include <QTcpSocket>
#include "protocol.h"

Interpreter::Interpreter(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    socket(socket)
{
    if (socket)
        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Interpreter::setSocket(QTcpSocket *socket, bool deleteOldSoscket)
{
    disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    buffer.clear();
    if (socket)
        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    if (deleteOldSoscket)
        delete this->socket;

    this->socket = socket;
}

void Interpreter::onReadyRead()
{
    buffer.append(socket->readAll());
    while (buffer.size()) {
        switch (buffer[0]) {
        case MOVEMENT:
            if (buffer.size() > 3) {
                emit movementRequest(MapEntity(buffer[1], buffer[2]),
                                     MapEntity::getPos(buffer[3]));
                buffer.remove(0, 4);
                break;
            } else {
                return;
            }
        case NEW_ENTITY:
            if (buffer.size() > 3) {
                emit newEntityRequest(MapEntity(buffer[1], buffer[2]),
                                      MapEntity::getPos(buffer[3]));
                buffer.remove(0, 4);
                break;
            } else {
                return;
            }
        case DESTROYED:
            if (buffer.size() > 2) {
                emit havocRequest(MapEntity(buffer[1], buffer[2]));
                buffer.remove(0, 3);
                break;
            } else {
                return;
            }
        default:
            emit streamError();
        }
    }
}
