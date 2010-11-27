#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include "mapentity.h"

class QTcpSocket;

class Interpreter : public QObject
{
Q_OBJECT
public:
    explicit Interpreter(QTcpSocket *socket, QObject *parent = 0);

signals:
    // can be caused by several reasons, like wrong protocol version,
    // hackers trying atack, ...
    void streamError();

    void movementRequest(MapEntity entity, QPoint newPos);
    void newEntityRequest(MapEntity entity, QPoint pos);
    void havocRequest(MapEntity entity);

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
    QByteArray buffer;
};

#endif // INTERPRETER_H
