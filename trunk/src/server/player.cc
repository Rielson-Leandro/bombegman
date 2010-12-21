#include "player.h"
#include "protocol.h"


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
    connect(world, SIGNAL(entityMoved(MapEntity*,char)), this, SLOT(onEntityMoved(MapEntity*,char)));
    connect(world, SIGNAL(newEntity(char,char,QPoint)), this, SLOT(onNewEntity(char,char,QPoint)));
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
            break;
        case INPUT:
            if (buffer.size() > 1)
            {
                switch ((int)(buffer[1])) {
                case BOMB_KEY_PRESS:
                    {
                        Bomb *bomb = new Bomb(world, this);
                        if (!world->addEntity(bomb,this->bomber->pos()))
                        {
                            delete bomb;
                        }

                        buffer.remove(0, 2);
                        break;
                    }
                case BOMB_KEY_RELEASE:
                    buffer.remove(0, 2);
                    break;
                default:
                    emit streamError();
                    return;
                }
            } else {
                return;
            }
            break;
        default:
            emit streamError();
            return;
        }
    }
}

void Player::decreaseActiveBombs()
{
    //TODO: check if it can be decreased.
    --activeBombs;
}

void Player::onEntityMoved(MapEntity *entity, char dir)
{
    char buffer[4] = {MOVEMENT, entity->getType(), entity->getId(), dir};
    socket->write(buffer, 4);
}

void Player::onNewEntity(char type, char id, QPoint pos)
{
    char buffer[4] = {NEW_ENTITY, type, id, getByte(pos)};
    socket->write(buffer, 4);
}
