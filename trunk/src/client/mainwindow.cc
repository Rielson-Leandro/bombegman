#include "mainwindow.h"
#include "connectdialog.h"
#include "world.h"
#include <QHostAddress>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(new QGraphicsScene),
    world(new World(scene))
{
    show();
    ConnectDialog *d = new ConnectDialog;

    while (!world->connectToHost(QHostAddress(d->hostAddress()), d->port())) {
        d->exec();
        if (d->result() == QDialog::Rejected) {
            hide();
            break;
        }
    }

    delete d;
}

MainWindow::~MainWindow()
{
}
