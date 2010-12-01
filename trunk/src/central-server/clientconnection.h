#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QHostAddress>

class QTcpSocket;
class Server;

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QTcpSocket *socket, Server *parent = 0);
    ~ClientConnection();

signals:
    void subscribe(QHostAddress client, QByteArray gameService, quint16 port,
                   int players_number, int players_max);
    void unsubscribe(QHostAddress client, QByteArray gameService, quint16 port);

private slots:
    void onReadyRead();

private:
    Server *server;
    QTcpSocket *socket;
    QByteArray buffer;
};

#endif // CLIENTCONNECTION_H
