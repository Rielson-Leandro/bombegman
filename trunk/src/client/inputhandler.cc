#include "inputhandler.h"

InputHandler::InputHandler(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
}
