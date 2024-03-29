#include "player.h"
#include "protocol.h"

Player::Player(QTcpSocket *socket, Bomber *bomber, QObject *parent) :
    QObject(parent),
    socket(socket),
    bomber(bomber),
    id(bomber->getId()),
    world(bomber->world()),
    activeBombs(0),
    maxBombs(2)
{
    movementLock.setSingleShot(true);

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
    connect(world, SIGNAL(entityMoved(MapEntity*,char)),
            this, SLOT(onEntityMoved(MapEntity*,char)));
    connect(world, SIGNAL(newEntity(char,char,QPoint)),
            this, SLOT(onNewEntity(char,char,QPoint)));
    connect(world, SIGNAL(entityDestroyed(char,char)),
            this, SLOT(onEntityDestroyed(char,char)));
    connect(world, SIGNAL(explosion(QPoint,int,int,int,int)),
            this, SLOT(onExplosion(QPoint,int,int,int,int)));
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
                if (!movementLock.isActive() && bomber) {
                    bomber->world()->requestMovement(bomber, buffer[1]);
                    movementLock.start(200);
                }

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
                    if (activeBombs < maxBombs && bomber) {
                        Bomb *bomb = new Bomb(world, this);
                        if (!world->addEntity(bomb,this->bomber->pos()))
                        {
                            delete bomb;
                        }
                        ++activeBombs;
                    }
                    buffer.remove(0, 2);
                    break;
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

void Player::onEntityDestroyed(char type, char id)
{
    if (id == this->id) {
        bomber = NULL;
    }
    char buffer[3] = {DESTROYED, type, id};
    socket->write(buffer, 3);
}

void Player::onExplosion(QPoint pos, int north, int east, int south, int west)
{
    char buffer[6] = {EXPLOSION, getByte(pos), north, east, south, west};
    socket->write(buffer, 6);
}
