#include "connectiondialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTcpSocket>

ConnectionDialog::ConnectionDialog(const QHostAddress &add, quint16 port,
                             QWidget *parent) :
        QWidget(parent),
        list(new QListWidget),
        socket(new QTcpSocket),
        host(add),
        port(port)
{
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onConnectButtonClicked()));

    QPushButton *connectButton = new QPushButton(QObject::tr("Connect"));
    connect(connectButton, SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));

    QPushButton *refreshButton = new QPushButton(QObject::tr("Refresh"));
    connect(refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshButtonCLicked()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(connectButton);
    buttonLayout->addWidget(refreshButton);

    connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(list);
    l->addLayout(buttonLayout);

    setLayout(l);
}

ConnectionDialog::~ConnectionDialog()
{
    delete list;
    delete socket;
}

void ConnectionDialog::onConnectButtonClicked()
{
    if (QListWidgetItem *i = list->currentItem()) {
        emit connectionRequested(QHostAddress(i->data(Qt::UserRole).toString()),
                                 i->data(Qt::UserRole + 1).toInt());
    }
}

void ConnectionDialog::onRefreshButtonCLicked()
{
    list->clear();
    socket->connectToHost(host, port);
}

void ConnectionDialog::onConnected()
{
    socket->write("LISTALL bombegman/0.2\n");
}

void ConnectionDialog::onReadyRead()
{
    buffer.append(socket->readAll());
    for (int i = buffer.indexOf('\n');buffer.indexOf('\n') != -1;i = buffer.indexOf('\n')) {
        if (buffer[0] == '\n') {
            buffer.remove(0, 1);
            break;
        }

        QList<QByteArray> game = buffer.left(i).split(' ');
        buffer.remove(0, i + 1);

        QListWidgetItem *item = new QListWidgetItem(QString(game[0]) + ':'
                                                    + QString(game[1]) + ' '
                                                    + QString(game[2]) + '/'
                                                    + QString(game[3]));

        item->setData(Qt::UserRole, QString(game[0]));
        item->setData(Qt::UserRole + 1, game[1].toInt());
        list->addItem(item);
    }
}
