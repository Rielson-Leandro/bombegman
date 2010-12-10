#include "player.h"
#include "world.h"

Player::Player(QTcpSocket* socket, Bomber *bomber, World *parent) :
    QObject(parent)
{
    this->socket = socket;
    this->bomber = bomber;
    quint8 id = bomber->getId();
    socket->write(reinterpret_cast <const char *> (&id), 1);
}

Player::~Player()
{
}

void Player::onReadyRead()
{
    buffer.append(socket->readAll());
    if (buffer.size() > 1) {
        switch (buffer[0]) {
        case 'R':
            if (buffer[1] == 'G') {
                emit matchRequest();
            } else {
                emit streamError();
            }
            break;
        default:
            emit streamError();
        }
    }
}
