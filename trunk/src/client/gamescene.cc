#include "gamescene.h"
#include "inputhandler.h"

GameScene::GameScene(InputHandler *inputHandler, QObject *parent) :
    QGraphicsScene(0, 0, 800, 600, parent),
    inputHandler(inputHandler)
{
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    inputHandler->keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    inputHandler->keyReleaseEvent(event);
}
