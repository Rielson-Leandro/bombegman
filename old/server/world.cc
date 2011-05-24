#include "world.h"
#include "protocol.h"
#include "player.h"

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
    if(players.size() <= 4 && (!players.size() || players.size() > matchRequestsNumber))
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

void World::requestExplosion(const QPoint &pos, int range)
{
    QSet<MapEntity *> deadEntities;
    //Exploding all entities in a cross with the given range.
    bool foundObstruction = false;

    //First let's explode in the X direction:
        //To the left:
    int leftRange = 0;
    for(int i = 0; i >= -range && !foundObstruction; i--)
    {
        if (map->getTile(pos.x() + i, pos.y()).space != Map::Tile::EMPTY) {
            foundObstruction = true;
            --leftRange;
        }
        if (map->getTile(pos.x() + i, pos.y()).space == Map::Tile::BRICK) {
            map->getTile(pos.x() + i, pos.y()).space = Map::Tile::EMPTY;
            emit entityDestroyed(TILE, getByte(QPoint(pos.x() + i, pos.y())));
        }

        foreach(MapEntity *e, map->getTile(pos.x() + i, pos.y()).entities)
        {
            if (e->obstructive())
                foundObstruction = true;
            e->explode();
            deadEntities << e;
        }
        ++leftRange;
    }
        //To the right:
    int rightRange = 0;
    foundObstruction = false;
    for(int i = 0; i <= range && !foundObstruction; i++)
    {
        if (map->getTile(pos.x() + i, pos.y()).space != Map::Tile::EMPTY) {
            foundObstruction = true;
            --rightRange;
        }
        if (map->getTile(pos.x() + i, pos.y()).space == Map::Tile::BRICK) {
            map->getTile(pos.x() + i, pos.y()).space = Map::Tile::EMPTY;
            emit entityDestroyed(TILE, getByte(QPoint(pos.x() + i, pos.y())));
        }

        foreach(MapEntity *e, map->getTile(pos.x() + i, pos.y()).entities)
        {
            if (e->obstructive())
                foundObstruction = true;
            e->explode();
            deadEntities << e;
        }
        ++rightRange;
    }

    //Now, we must do the same to the Y direction:
        //Upwards:
    foundObstruction = false;
    int upwardsRange = 0;
    for(int i = 0; i >= -range && !foundObstruction; i--)
    {
        if (map->getTile(pos.x(), pos.y() + i).space != Map::Tile::EMPTY) {
            foundObstruction = true;
            --upwardsRange;
        }
        if (map->getTile(pos.x(), pos.y() + i).space == Map::Tile::BRICK) {
            map->getTile(pos.x(), pos.y() + i).space = Map::Tile::EMPTY;
            emit entityDestroyed(TILE, getByte(QPoint(pos.x(), pos.y() + i)));
        }

        foreach(MapEntity *e, map->getTile(pos.x(), pos.y() + i).entities)
        {
            if (e->obstructive())
                foundObstruction = true;
            e->explode();
            deadEntities << e;
        }
        ++upwardsRange;
    }
        //And downwards:
    foundObstruction = false;
    int downwardsRange = 0;
    for(int i = 0; i <= range && !foundObstruction; i++)
    {
        if (map->getTile(pos.x(), pos.y() + i).space != Map::Tile::EMPTY) {
            foundObstruction = true;
            --downwardsRange;
        }
        if (map->getTile(pos.x(), pos.y() + i).space == Map::Tile::BRICK) {
            map->getTile(pos.x(), pos.y() + i).space = Map::Tile::EMPTY;
            emit entityDestroyed(TILE, getByte(QPoint(pos.x(), pos.y() + i)));
        }

        foreach(MapEntity *e, map->getTile(pos.x(), pos.y() + i).entities)
        {
            if (e->obstructive())
                foundObstruction = true;
            e->explode();
            deadEntities << e;
        }
        ++downwardsRange;
    }

    //Collecting the dead bodies:
    foreach (MapEntity *e, deadEntities) {
        emit entityDestroyed(e->getType(), e->getId());
        map->removeEntity(e);
//        delete e;
    }

    emit explosion(pos, upwardsRange, rightRange, downwardsRange, leftRange);
}

