#ifndef WORLD_H
#define WORLD_H

#include <QObject>

class QTcpSocket;
class QHostAddress;
class QGraphicsScene;
class Interpreter;
class Formatter;
class Drawer;
class InputHandler;

class World : public QObject
{
Q_OBJECT
public:
    explicit World(QGraphicsScene *scene, QObject *parent = 0);
    ~World();

    bool connectToHost(const QHostAddress &address, quint16 port);

signals:

public slots:

private:
    QTcpSocket *socket;
    Interpreter *interpreter;
    Formatter *formatter;
    Drawer *drawer;
    InputHandler *inputHandler;
};

#endif // WORLD_H
