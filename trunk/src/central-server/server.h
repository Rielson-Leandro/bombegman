#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QList>
#include <QHash>

struct Game
{
    QHostAddress server;
    quint16 port;
    int players_num;
    int players_max;

    Game() {}
    Game(const QHostAddress &a, quint16 p, int pn, int pm) : server(a), port(p), players_num(pn), players_max(pm) {}
};

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    QList<Game> games(const QByteArray &gameService);

private slots:
    void onNewConnection();

    void onSubscribe(QHostAddress server, QByteArray gameService, quint16 port,
                     int players_num, int players_max);
    void onUnsubscribe(QHostAddress server, QByteArray gameService, quint16 port);
//    void onUnsubscribeConfirm(QHostAddress client, QByteArray gameService, quint16 port);

private:
    QHash<QByteArray, QList<Game> > services;
};

#endif // SERVER_H
