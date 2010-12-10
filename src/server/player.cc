#include "player.h"
#include "world.h"
#include "protocol.h"

Player::Player(QTcpSocket *socket, Bomber *bomber, QObject *parent) :
    QObject(parent),
    socket(socket),
    bomber(bomber),
    world(bomber->world())
{
    qDebug("Jesus Cristo ... estou aqui");
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
    qDebug("lendo bytes");
    buffer.append(socket->readAll());
    if (buffer.size() > 1) {
        switch (buffer[0]) {
        case REQUEST:
            if (buffer[1] == MATCH) {
                qDebug("pronto para jogar");
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
