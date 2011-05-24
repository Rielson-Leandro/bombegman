#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class InputHandler;

class GameScene : public QGraphicsScene
{
Q_OBJECT
public:
    explicit GameScene(InputHandler *inputHandler, QObject *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    InputHandler *inputHandler;
};

#endif // GAMESCENE_H
