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
    explicit Player(QTcpSocket *socket, Bomber *bomber, World *parent);
    ~Player();

signals:
    void matchRequest();
    void streamError();

private slots:
    void onReadyRead();

private:
    Bomber *bomber;
    QTcpSocket *socket;
    QByteArray buffer;
};

#endif // PLAYER_H
