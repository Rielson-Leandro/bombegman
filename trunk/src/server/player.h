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

signals:
    void matchRequest();
    void streamError();

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
    QByteArray buffer;
    Bomber *bomber;
    World *world;
};

#endif // PLAYER_H
