#include "mainwindow.h"
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QStatusBar>
#include <QHostInfo>
#include <QLabel>
#include "connectdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    textEdit(new QPlainTextEdit),
    textBrowser(new QTextEdit),
    socket(new QTcpSocket),
    status(new QLabel),
    host("127.0.0.1"),
    port(8080)
{
    connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    QPushButton *button = new QPushButton("Send");
    connect(button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    textBrowser->setReadOnly(true);

    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(textEdit);
    l->addWidget(textBrowser);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(l);
    mainLayout->addWidget(button);

    QWidget *w = new QWidget;
    w->setLayout(mainLayout);
    setCentralWidget(w);

    QMenuBar *menubar = new QMenuBar;
    QMenu *mainMenu = menubar->addMenu("Connection");
    mainMenu->addAction("Connect to host", this, SLOT(onConnectionRequest()));
    mainMenu->addAction("Reconnect to last host", this, SLOT(onReconnectionRequest()));
    mainMenu->addAction("Disconnect", this, SLOT(onDisconnectionRequest()));

    setMenuBar(menubar);

    QStatusBar *bar = new QStatusBar;
    bar->insertPermanentWidget(0, status);
    setStatusBar(bar);
}

MainWindow::~MainWindow()
{
    delete socket;
}

void MainWindow::onButtonClicked()
{
    socket->write(textEdit->toPlainText().toUtf8());
    status->setText("Sending bytes to host");
}

void MainWindow::onConnectionRequest()
{
    ConnectDialog *d = new ConnectDialog(host, port, this);

    if (d->exec() == QDialog::Accepted) {
        host = d->hostAddress();
        port = d->portAddress();

        QHostAddress a(host);

        if (a.isNull()) {
            QHostInfo h = QHostInfo::fromName(host);
            if (h.error() == QHostInfo::NoError) {
                a = h.addresses()[qrand() % h.addresses().size()];
            }
        }

        if (!a.isNull()) {
            socket->close();
            socket->connectToHost(a, port);
        } else {
            status->setText("Couldn't connect");
        }
    }

    delete d;
}

void MainWindow::onReconnectionRequest()
{
    QHostAddress a(host);

    if (a.isNull()) {
        QHostInfo h = QHostInfo::fromName(host);
        if (h.error() == QHostInfo::NoError) {
            a = h.addresses()[qrand() % h.addresses().size()];
        }
    }

    if (!a.isNull()) {
        socket->close();
        socket->connectToHost(a, port);
    } else {
        status->setText("Couldn't connect");
    }
}

void MainWindow::onDisconnectionRequest()
{
    socket->close();
}

void MainWindow::onConnected()
{
    status->setText("Connected");
    textBrowser->clear();
}

void MainWindow::onDisconnected()
{
    status->setText("Disconnected");
}

void MainWindow::onReadyRead()
{
    QTextCursor cursor(textBrowser->document());
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(socket->readAll());
}
