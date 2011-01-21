#include "mainwindow.h"
#include "world.h"
#include <QGraphicsView>
#include "gamescene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    view(new QGraphicsView),
    world(new World)
{
    view->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    view->setScene(world->scene());
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
}
