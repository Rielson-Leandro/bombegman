#include "server.h"
#include "clientconnection.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void Server::onNewConnection()
{
    ClientConnection *c = new ClientConnection(nextPendingConnection(), this);

    connect(c, SIGNAL(subscribe(QHostAddress,QByteArray,quint16,int,int)),
            this, SLOT(onSubscribe(QHostAddress,QByteArray,quint16,int,int)));
    connect(c, SIGNAL(unsubscribe(QHostAddress,QByteArray,quint16)),
            this, SLOT(onUnsubscribe(QHostAddress,QByteArray,quint16)));
}

QList<Game> Server::games(const QByteArray &gameService)
{
    return services[gameService];
}

void Server::onSubscribe(QHostAddress server, QByteArray gameService, quint16 port, int players_num, int players_max)
{
    QList<Game> &games = services[gameService];
    games.append(Game(server, port, players_num, players_max));

    int i = 0;
    for (;i < games.size(); ++i) {
        if (games[i].server == server && games[i].port == port)
            break;
    }

    if (i != games.size() - 1)
        games.pop_back();

    games[i].port = port;
    games[i].players_num = players_num;
    games[i].players_max = players_max;
}

void Server::onUnsubscribe(QHostAddress server, QByteArray gameService, quint16 port)
{
    QList<Game> &games = services[gameService];

    for (int i = 0;i < games.size();++i) {
        if (games[i].server == server && games[i].port == port) {
            games.removeAt(i);
            break;
        }
    }
}
