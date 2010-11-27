#include "menuscene.h"
#include "connectdialog.h"
#include <QGraphicsProxyWidget>

MenuScene::MenuScene(QObject *parent) :
    QGraphicsScene(0, 0, 800, 600, parent),
    connectionDialog(new ConnectDialog)
{
    QGraphicsProxyWidget *widgetItem = new QGraphicsProxyWidget;
    connect(connectionDialog, SIGNAL(connectionRequested()), this, SLOT(onConnectionRequested()));

    widgetItem->setWidget(connectionDialog);
    addItem(widgetItem);
}

void MenuScene::onConnectionRequested()
{
    emit connectionRequested(QHostAddress(connectionDialog->hostAddress()),
                             connectionDialog->port());
}
