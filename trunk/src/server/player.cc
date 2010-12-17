#include "player.h"
#include "world.h"
#include "protocol.h"

Player::Player(QTcpSocket *socket, Bomber *bomber, QObject *parent) :
    QObject(parent),
    socket(socket),
    bomber(bomber),
    world(bomber->world())
{
    qDebug("A client has connected...");
    quint8 id = bomber->getId();
    socket->write(reinterpret_cast <const char *> (&id), 1);

    if (socket->size())
        onReadyRead();
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
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
        default:
            emit streamError();
        }
    }
}