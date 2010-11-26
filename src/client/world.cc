#include "world.h"
#include <QTcpSocket>
#include "interpreter.h"
#include "formatter.h"
#include "drawer.h"
#include "inputhandler.h"

World::World(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket),
    interpreter(new Interpreter(socket)),
    formatter(new Formatter(socket)),
    drawer(new Drawer(scene)),
    inputHandler(new InputHandler(scene))
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
