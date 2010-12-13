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
class GameScene;

class World : public QObject
{
Q_OBJECT
public:
    explicit World(QObject *parent = 0);
    ~World();

    bool connectToHost(const QHostAddress &address, quint16 port);

    QGraphicsScene *scene();

private:
    InputHandler *inputHandler;
    GameScene *gameScene;
    Drawer *drawer;
    QTcpSocket *socket;
    Interpreter *interpreter;
    Formatter *formatter;
};

#endif // WORLD_H
