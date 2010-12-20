#ifndef WORLD_H
#define WORLD_H


#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QSettings>

#include "map.h"
#include "player.h"
#include "mapentity.h"
#include "bomber.h"


class World : public QObject
{
Q_OBJECT
public:
    explicit World(const QHostAddress &hostAddress, quint16 port, QObject *parent = 0);
    ~World();

    bool requestMovement(MapEntity *entity, char dir);
    void requestExplosion(const QPoint &);

    // time is in miliseconds
    void startMatch(int matchTimeLimit);

    void start(const QHostAddress &subscriptionServerHostAddress = QHostAddress(), quint16 subscriptionServerPort = 0);

    void removeEntity(MapEntity *entity);

    const Map &getMap() const;

signals:
    void entityMoved(MapEntity *entity, char dir);

private slots:
    void onNewConnection();

    void onSubscriptionServerConnected();

private:
    void subscribeToServer(const QHostAddress &host, quint16 port);

private:
    QHostAddress subscriptionServerHostAddress;
    quint16 subscriptionServerPort;

    QHostAddress host;
    quint16 port;
    QTcpServer *server;

    QList<Player*> players;
    Map *map;
};

#endif // WORLD_H