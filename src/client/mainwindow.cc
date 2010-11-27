#include "mainwindow.h"
#include "world.h"
#include <QHostAddress>
#include <QGraphicsView>
#include "menuscene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    menuScene(new MenuScene),
    gameScene(new QGraphicsScene),
    view(new QGraphicsView(menuScene)),
    world(new World(gameScene))
{
    view->viewport()->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onConnectionRequested(const QHostAddress &address, quint16 port)
{
    if (world->connectToHost(address, port)) {
        view->setScene(gameScene);
    }
}
