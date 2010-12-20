#include "world.h"
#include "protocol.h"

World::World(const QHostAddress &hostAddress, quint16 port, QObject *parent) :
        QObject(parent),
        host(hostAddress),
        port(port),
        server(new QTcpServer),
        matchRequestsNumber(0),
        map(new Map)
{
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

World::~World()
{
    delete server;
    delete map;
}

void World::start(const QHostAddress &subscriptionServerHostAddress, quint16 subscriptionServerPort)
{
    map->generateMap();
    server->listen(host, port);
    subscribeToServer(subscriptionServerHostAddress, subscriptionServerPort);
}

void World::onSubscriptionServerConnected()
{
    QTcpSocket *s = static_cast<QTcpSocket *>(sender());
    s->write(QByteArray("SUBSCRIBE bombegman/0.2 ")
             + QByteArray::number(port) + ' '
             + QByteArray::number(players.size()) + ' ' + "4\n");
    connect(s, SIGNAL(disconnected()), s, SLOT(deleteLater()));
}

void World::subscribeToServer(const QHostAddress &host, quint16 port)
{
    QTcpSocket *s = new QTcpSocket(this);
    connect(s, SIGNAL(connected()), this, SLOT(onSubscriptionServerConnected()));
    s->connectToHost(host, port);
}

void World::onNewConnection()
{
    if(players.size() <= 4)
    {
        QTcpSocket *socket = server->nextPendingConnection();
        Bomber *bomber = new Bomber(this);
        switch (players.size()) {
        case 0:
            map->addMapEntity(bomber, QPoint(1, 1));
            break;
        case 1:
            map->addMapEntity(bomber, map->getDimensions() - QPoint(2, 2));
            break;
        case 2:
            map->addMapEntity(bomber, QPoint(map->getDimensions().x() - 2, 1));
            break;
        case 3:
            map->addMapEntity(bomber, QPoint(1, map->getDimensions().y() - 2));
        }

        Player *player = new Player(socket, bomber, this);
        players.append(player);
        connect(player, SIGNAL(matchRequest()), this, SLOT(onMatchRequest()));

        subscribeToServer(subscriptionServerHostAddress, subscriptionServerPort);
    }else{
        delete server->nextPendingConnection();
    }
}

void World::onMatchRequest()
{
    if (++matchRequestsNumber == players.size()) {
        foreach (Player *player, players) {
            Bomber *bomber = player->getBomber();
            emit newEntity(PLAYER, bomber->getId(), bomber->pos());
        }
    }
}

void World::removeEntity(MapEntity *entity)
{
    map->removeEntity(entity);
}

bool World::addEntity(MapEntity *entity, QPoint pos)
{
    bool wasPossible = map->addMapEntity(entity, pos);
    if ( wasPossible )
    {
        emit newEntity(entity->getType(), entity->getId(), pos);
    }
    return wasPossible;
}

bool World::requestMovement(MapEntity *entity, char dir)
{
    QPoint pos = entity->pos();
    switch (dir)
    {
    case NORTH:
        pos.ry()--;
        break;
    case SOUTH:
        pos.ry()++;
        break;
    case EAST:
        pos.rx()++;
        break;
    case WEST:
        pos.rx()--;
        break;
    default:
        return false;
    }
    if (map->setPos(entity, pos)){
        qDebug("Position changed.");
        emit entityMoved(entity, dir);
        return true;
    } else {
        return false;
    }
}

const Map &World::getMap() const
{
    return *map;
}

void World::onDestructionRequested(QPoint pos, int range)
{
    //Exploding all entities in a cross with the given range.
    for(int i = -range; i <= range; i++)
    {
        foreach(MapEntity *e, this->map->getTile(pos.x() + i, pos.y()).entities)
        {
            e->explode();
        }

        foreach(MapEntity *e, this->map->getTile(pos.x(), pos.y() + i).entities)
        {
            e->explode();
        }
    }
}
