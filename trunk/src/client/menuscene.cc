#include "menuscene.h"
#include "connectdialog.h"
#include <QGraphicsProxyWidget>

MenuScene::MenuScene(QObject *parent) :
    QGraphicsScene(0, 0, 800, 600, parent),
    connectionDialog(new ConnectDialog(QHostAddress::LocalHost, 8080))
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
