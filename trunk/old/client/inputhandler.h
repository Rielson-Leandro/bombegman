#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include "mapentity.h"

class QGraphicsScene;
class QKeyEvent;

class InputHandler : public QObject
{
Q_OBJECT
public:
    explicit InputHandler(QObject *parent = 0);

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

signals:
    void requestMovement(char dir);
    void requestInput(char type);
};

#endif // INPUTHANDLER_H
