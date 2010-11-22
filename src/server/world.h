#ifndef WORLD_H
#define WORLD_H

#include <QObject>

class MapObject;
class QPoint;
class QTcpSocket;

class World : public QObject
{
Q_OBJECT
public:
    explicit World(QObject *parent = 0);

    void requestMovement(MapObject *, const QPoint &);
    void requestExplosion(const QPoint &);

    void addPlayer(QTcpSocket *);

    // time is in miliseconds
    void startMatch(int matchTimeLimit);

signals:

public slots:

};

#endif // WORLD_H
