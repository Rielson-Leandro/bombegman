#include "inputhandler.h"

#include "protocol.h"

InputHandler::InputHandler(QObject *parent) :
    QObject(parent)
{
}

void InputHandler::keyPressEvent(QKeyEvent *e)
{
    // TODO
//    emit requestInput(BOMB_KEY_PRESS);
//    emit requestInput(BOMB_KEY_RELEASE);
}

void InputHandler::keyReleaseEvent(QKeyEvent *e)
{
    // TODO
    //    emit requestInput(BOMB_KEY_PRESS);
    //    emit requestInput(BOMB_KEY_RELEASE);
}
