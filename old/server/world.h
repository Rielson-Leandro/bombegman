#ifndef WORLD_H
#define WORLD_H


#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QSettings>
#include <QPoint>

#include "map.h"
#include "mapentity.h"
#include "bomber.h"

class Player;


class World : public QObject
{
Q_OBJECT
public:
    explicit World(const QHostAddress &hostAddress, quint16 port, QObject *parent = 0);
    ~World();

    bool requestMovement(MapEntity *entity, char dir);
    void requestExplosion(const QPoint &pos, int range);

    // time is in miliseconds
    void startMatch(int matchTimeLimit);

    void start(const QHostAddress &subscriptionServerHostAddress = QHostAddress(), quint16 subscriptionServerPort = 0);

    bool addEntity(MapEntity *entity, QPoint pos);
    void removeEntity(MapEntity *entity);

    const Map &getMap() const;

signals:
    void entityMoved(MapEntity *entity, char dir);
    void newEntity(char type, char id, QPoint pos);
    void entityDestroyed(char type, char id);
    void explosion(QPoint pos, int north, int east, int south, int west);

private slots:
    void onNewConnection();
    void onSubscriptionServerConnected();
    void onMatchRequest();

private:
    void subscribeToServer(const QHostAddress &host, quint16 port);

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
