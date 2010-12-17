#include "interpreter.h"
#include <QTcpSocket>
#include "protocol.h"
#include <QDebug>

enum State
{
    WAITING_FOR_ID,
    WAITING_FOR_MAP_DIMENSIONS,
    WAITING_FOR_MAP_TILES,
    WAITING_FOR_ACTION
};

Interpreter::Interpreter(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    socket(socket),
    state(WAITING_FOR_ID)
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
    bool idRead;
    buffer.append(socket->readAll());
    while (buffer.size()) {
        switch (state) {
        case WAITING_FOR_ID:
            quint8 id;
            id = buffer[0];
            buffer.remove(0, 1);
            idRead = true;
            emit idReceived(id);
            ++state;
            break;
        case WAITING_FOR_MAP_DIMENSIONS:
            mapDimensions = MapEntity::getPos(buffer[0]);
            buffer.remove(0, 1);
            ++state;
            break;
        case WAITING_FOR_MAP_TILES:
            if (buffer.size() >= mapDimensions.x() * mapDimensions.y()) {
                int k = 0;
                for (int j = 0;j < mapDimensions.y();++j) {
                    for (int i = 0;i < mapDimensions.x();++i) {
                        mapBuffer[i][j] = buffer[k++];
                    }
                }
                buffer.remove(0, mapDimensions.x()*mapDimensions.y());
                emit mapReceived(mapDimensions, mapBuffer);
                ++state;
            }
            break;
        case WAITING_FOR_ACTION:
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
                buffer.clear();
                return;
            }
        }
    }
}
