#ifndef WORLD_H
#define WORLD_H


#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QSettings>
#include <QPoint>

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

    bool addEntity(MapEntity *entity, QPoint pos);
    void removeEntity(MapEntity *entity);

    const Map &getMap() const;
    void onDestructionRequested(QPoint pos, int range);

signals:
    void entityMoved(MapEntity *entity, char dir);
    void newEntity(char type, char id, QPoint pos);

private slots:
    void onNewConnection();

    void onSubscriptionServerConnected();

    void onMatchRequest();

private:
    void subscribeToServer(const QHostAddress &host, quint16 port);

private:
    QHostAddress subscriptionServerHostAddress;
    quint16 subscriptionServerPort;

    QHostAddress host;
    quint16 port;
    QTcpServer *server;

    QList<Player*> players;
    int matchRequestsNumber;

    Map *map;
};

#endif // WORLD_H
