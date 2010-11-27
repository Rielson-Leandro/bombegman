#ifndef FORMATTER_H
#define FORMATTER_H

#include <QObject>
#include "mapentity.h"

class QTcpSocket;

class Formatter : public QObject
{
Q_OBJECT
public:
    explicit Formatter(QTcpSocket *socket, QObject *parent = 0);

public slots:
    void requestMovement(MapEntity entity, QPoint newPos);
    void requestBomb();

private:
    QTcpSocket *socket;
};

#endif // FORMATTER_H
