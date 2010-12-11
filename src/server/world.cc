#include "world.h"


World::World(const QHostAddress &hostAddress, quint16 port, QObject *parent) :
        QObject(parent),
        host(hostAddress),
        port(port),
        server(new QTcpServer)
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
    server->listen(host, port);
    subscribeToServer(subscriptionServerHostAddress, subscriptionServerPort);
}

void World::onSubscriptionServerConnected()
{
    QTcpSocket *s = static_cast<QTcpSocket *>(sender());
    s->write(QByteArray("SUBSCRIBE ")
             + "bombegman/0.2 " + QByteArray::number(port) + ' '
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
        players.append(new Player(socket, bomber, this));
        subscribeToServer(subscriptionServerHostAddress, subscriptionServerPort);
    }else{
        delete server->nextPendingConnection();
    }
}

void World::removeEntity(MapEntity *entity)
{
    map->removeEntity(entity);
}
