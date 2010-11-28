#include "world.h"
#include <QTcpSocket>
#include "interpreter.h"
#include "formatter.h"
#include "drawer.h"
#include "inputhandler.h"
#include "gamescene.h"

World::World(QObject *parent) :
    QObject(parent),
    inputHandler(new InputHandler),
    gameScene(new GameScene(inputHandler)),
    drawer(new Drawer(gameScene)),
    socket(new QTcpSocket),
    interpreter(new Interpreter(socket)),
    formatter(new Formatter(socket))
{
}

World::~World()
{
    delete socket;
}

bool World::connectToHost(const QHostAddress &address, quint16 port)
{
    socket->connectToHost(address, port);
    return socket->waitForConnected();
}

QGraphicsScene *World::scene()
{
    return gameScene;
}
