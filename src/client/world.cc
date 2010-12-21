#include "world.h"
#include <QTcpSocket>
#include "interpreter.h"
#include "formatter.h"
#include "drawer.h"
#include "inputhandler.h"
#include "gamescene.h"
#include <QDebug>
#include <QMetaMethod>

World::World(QObject *parent) :
    QObject(parent),
    inputHandler(new InputHandler),
    gameScene(new GameScene(inputHandler)),
    drawer(new Drawer(gameScene)),
    socket(new QTcpSocket),
    interpreter(new Interpreter(socket)),
    formatter(new Formatter(socket))
{
    connect(inputHandler, SIGNAL(requestMovement(char)),
            formatter, SLOT(requestMovement(char)));
    connect(inputHandler, SIGNAL(requestInput(char)),
            formatter, SLOT(requestInput(char)));

    connect(interpreter, SIGNAL(newEntityRequest(MapEntity,QPoint)),
            drawer, SLOT(requestNewEntity(MapEntity,QPoint)));
    connect(interpreter, SIGNAL(movementRequest(MapEntity,char)),
            drawer, SLOT(requestMovement(MapEntity,char)));
    connect(interpreter, SIGNAL(entityDestroyedRequest(MapEntity)),
            drawer, SLOT(requestEntityDestroyed(MapEntity)));
    connect(interpreter, SIGNAL(explosionRequest(QPoint,int,int,int,int)),
            drawer, SLOT(requestExplosion(QPoint,int,int,int,int)));
    connect(interpreter, SIGNAL(mapReceived()), this, SLOT(onMapReceived()));

    connect(drawer, SIGNAL(removeButtonClicked()),
            formatter, SLOT(requestMatch()));
    connect(drawer, SIGNAL(removeButtonClicked()),
            drawer, SLOT(removeReadyButton()));
}

void World::onMapReceived()
{
    QPair<QPoint, char(*)[16]> map = interpreter->getMap();
    drawer->prepareMap(map.first, map.second);
    drawer->addReadyButton();
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
