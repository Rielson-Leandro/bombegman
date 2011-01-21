#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class World;
class QHostAddress;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QGraphicsScene *menuScene;
    QGraphicsView *view;
    World *world;
};

#endif // MAINWINDOW_H
