#include "mainwindow.h"
#include "world.h"
#include <QHostAddress>
#include <QGraphicsView>
#include "menuscene.h"
#include "gamescene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    menuScene(new MenuScene),
    view(new QGraphicsView(menuScene)),
    world(new World)
{
    view->viewport()->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);
    connect(static_cast<MenuScene *>(menuScene), SIGNAL(connectionRequested(QHostAddress,quint16)),
            this, SLOT(onConnectionRequested(QHostAddress,quint16)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::onConnectionRequested(const QHostAddress &address, quint16 port)
{
    if (world->connectToHost(address, port)) {
        view->setScene(world->scene());
    }
}
