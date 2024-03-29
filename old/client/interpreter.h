#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include "mapentity.h"
#include <QPair>

class QTcpSocket;

class Interpreter : public QObject
{
Q_OBJECT
public:
    explicit Interpreter(QTcpSocket *socket = NULL, QObject *parent = 0);

    void setSocket(QTcpSocket *socket, bool deleteOldSoscket = true);
    QPair<QPoint, char(*)[16]> getMap();

signals:
    // can be caused by several reasons, like wrong protocol version,
    // hackers trying atack, ...
    void streamError();

    void idReceived(quint8);
    void mapReceived();

    void movementRequest(MapEntity entity, char dir);
    void newEntityRequest(MapEntity entity, QPoint pos);
    void entityDestroyedRequest(MapEntity entity);
    void explosionRequest(QPoint, int north, int east, int south, int west);

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
    QByteArray buffer;

    int state;
    QPoint mapDimensions;
    char mapBuffer[16][16];
};

#endif // INTERPRETER_H
