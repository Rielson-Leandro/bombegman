#include "player.h"
#include "world.h"
#include "protocol.h"
#include "mapentity.h"

inline QPoint getPos(unsigned char byte)
{
    const int x = (byte & 0xF0) >> 4;
    const int y = byte & 0x0F;
    return QPoint(x, y);
}

inline unsigned char getByte(QPoint point)
{
    const unsigned char x = point.x(), y = point.y();
    unsigned char byte = x << 4;
    byte |= y;
    return byte;
}

Player::Player(QTcpSocket *socket, Bomber *bomber, QObject *parent) :
    QObject(parent),
    socket(socket),
    bomber(bomber),
    world(bomber->world())
{
    qDebug("A client has connected...");
    quint8 id = bomber->getId();
    socket->write(reinterpret_cast <const char *> (&id), 1);

    const Map &map = bomber->world()->getMap();
    QPoint dimensions = map.getDimensions();

    socket->write(QByteArray(1, getByte(dimensions - QPoint(1, 1))));

    for (int j = 0; j < dimensions.y(); ++j) {
        for (int i = 0; i < dimensions.x(); ++i) {
            socket->write(QByteArray(1, map.getTile(i, j).space));
        }
    }

    if (socket->size())
        onReadyRead();

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Player::sendNewEntity(char type, char id, QPoint pos)
{
    char buffer[4] = {NEW_ENTITY, type, id, getByte(pos)};
    socket->write(buffer, 4);
}

Player::~Player()
{
}

void Player::onReadyRead()
{
    qDebug("Reading bytes");
    buffer.append(socket->readAll());
    while (buffer.size())
    {
        switch (buffer[0])
        {
        case REQUEST:
            if (buffer.size() > 1)
            {
                if((int)(buffer[1]) == MATCH)
                {
                    qDebug("Ready to play");
                    buffer.remove(0, 2);
                    emit matchRequest();
                } else {
                    emit streamError();
                    buffer.clear();
                    return;
                }
            } else {
                return;
            }
            break;
        case MOVEMENT:
            if (buffer.size() > 1)
            {
                if (bomber->world()->requestMovement(bomber, buffer[1]))
                    qDebug("Player %i moving %c", (int)(bomber->getId()), (char)(buffer[1]));

                buffer.remove(0, 2);
            } else {
                return;
            }
        case INPUT:
            if (buffer.size() > 1)
            {
                if ((int)(buffer[1]) == BOMB_KEY_PRESS)
                {
                    qDebug("Bomb holding not yet implemented");
                }
                if ((int)(buffer[1]) == BOMB_KEY_RELEASE)
                {
                    qDebug("Player %i has released a bomb", (int)(bomber->getId()));

                }
            }
        default:
            emit streamError();
        }
    }
}

void Player::decreaseActiveBombs()
{
    //TODO: check if it can be decreased.
    activeBombs--;
}
