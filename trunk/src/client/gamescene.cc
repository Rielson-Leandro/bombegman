#include "gamescene.h"
#include "inputhandler.h"

GameScene::GameScene(InputHandler *inputHandler, QObject *parent) :
    QGraphicsScene(parent),
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
