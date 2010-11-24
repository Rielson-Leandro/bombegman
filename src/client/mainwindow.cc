#include "mainwindow.h"
#include "connectdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ConnectDialog *d = new ConnectDialog;
    d->exec();
    qDebug("%s:%i", d->hostAddress().toAscii().constData(), d->port());
    delete d;
}

MainWindow::~MainWindow()
{
}
