#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>

class QGraphicsScene;

class InputHandler : public QObject
{
Q_OBJECT
public:
    explicit InputHandler(QGraphicsScene *scene, QObject *parent = 0);

signals:

public slots:

private:
    QGraphicsScene *scene;
};

#endif // INPUTHANDLER_H
