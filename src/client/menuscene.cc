#include "menuscene.h"
#include "connectdialog.h"
#include <QGraphicsProxyWidget>

#define DEFAULT_CENTRAL_SERVER_HOST "192.168.7.81"
#define DEFAULT_CENTRAL_SERVER_PORT 50000

MenuScene::MenuScene(QObject *parent) :
    QGraphicsScene(0, 0, 800, 600, parent),
    connectionDialog(new ConnectDialog(QHostAddress(DEFAULT_CENTRAL_SERVER_HOST), DEFAULT_CENTRAL_SERVER_PORT))
{
    QGraphicsProxyWidget *widgetItem = new QGraphicsProxyWidget;
    connect(connectionDialog, SIGNAL(connectionRequested(QHostAddress,quint16)),
            this, SLOT(onConnectionRequested(QHostAddress,quint16)));

    widgetItem->setWidget(connectionDialog);
    addItem(widgetItem);
}

void MenuScene::onConnectionRequested(const QHostAddress &host, quint16 port)
{
    emit connectionRequested(host, port);
}
