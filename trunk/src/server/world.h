#ifndef WORLD_H
#define WORLD_H


#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QSettings>

#include "player.h"
#include "mapentity.h"



class World : public QObject
{
Q_OBJECT
public:
    explicit World(QObject *parent = 0);

    void requestMovement(MapEntity *, const QPoint &);
    void requestExplosion(const QPoint &);

    void addPlayer(QTcpSocket *);

    // time is in miliseconds
    void startMatch(int matchTimeLimit);

    void listen(QHostAddress hostAddress, quint16 port);

private:
    QTcpServer *server;


};

#endif // WORLD_H
