#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "bomber.h"

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

public slots:
    void sendNewEntity(char type, char id, QPoint pos);

private slots:
    void onReadyRead();
    void onEntityMoved(MapEntity*,char);
    void onNewEntity(char type, char id, QPoint pos);

private:
    QTcpSocket *socket;
    QByteArray buffer;
    Bomber *bomber;
    World *world;
    int activeBombs;
};

inline Bomber *Player::getBomber()
{
    return bomber;
}

#endif // PLAYER_H
