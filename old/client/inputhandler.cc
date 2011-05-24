#include "inputhandler.h"
#include <QKeyEvent>
#include "protocol.h"

InputHandler::InputHandler(QObject *parent) :
    QObject(parent)
{
}

void InputHandler::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Space:
        emit requestInput(BOMB_KEY_PRESS);
    case Qt::Key_Up:
    case Qt::Key_Right:
    case Qt::Key_Down:
    case Qt::Key_Left:
        e->accept();
        break;
    default:
        e->ignore();
    }
}

void InputHandler::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        emit requestMovement(NORTH);
        break;
    case Qt::Key_Right:
        emit requestMovement(EAST);
        break;
    case Qt::Key_Down:
        emit requestMovement(SOUTH);
        break;
    case Qt::Key_Left:
        emit requestMovement(WEST);
        break;
    case Qt::Key_Space:
        emit requestInput(BOMB_KEY_RELEASE);
    }
}
