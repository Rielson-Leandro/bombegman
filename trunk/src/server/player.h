#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "bomber.h"
#include "mapentity.h"
#include "bomb.h"
#include "world.h"

class World;

class QTcpSocket;

class Player : public QObject
{
Q_OBJECT
public:
    explicit Player(QTcpSocket *socket, Bomber *bomber, QObject *parent = NULL);
    ~Player();
    void decreaseActiveBombs();
    Bomber *getBomber();

signals:
    void matchRequest();
    void streamError();

private slots:
    void onReadyRead();
    void onEntityMoved(MapEntity *entity, char dir);
    void onNewEntity(char type, char id, QPoint pos);
    void onEntityDestroyed(char type, char id);
    void onExplosion(QPoint pos, int north, int east, int south, int west);

private:
    QTcpSocket *socket;
    QByteArray buffer;
    Bomber *bomber;
    World *world;
    int activeBombs;
    int maxBombs;
    QTimer movementLock;
};

inline Bomber *Player::getBomber()
{
    return bomber;
}

#endif // PLAYER_H
