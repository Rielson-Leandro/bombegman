#include "clientconnection.h"
#include <QTcpSocket>
#include <QTextStream>
#include "server.h"

namespace Message
{
    static const QByteArray subscribe("SUBSCRIBE ");
    static const QByteArray unsubscribe("UNSUBSCRIBE ");
    static const QByteArray listall("LISTALL ");
}

ClientConnection::ClientConnection(QTcpSocket *socket, Server *parent) :
    QObject(parent),
    server(parent),
    socket(socket)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

ClientConnection::~ClientConnection()
{
    delete socket;
}

void ClientConnection::onReadyRead()
{
    buffer.append(socket->readAll());

    if (buffer.contains('\n')) {
        QByteArray gameService;
        QTextStream stream(&buffer);

        if (buffer.startsWith(Message::subscribe)) {
            buffer.remove(0, Message::subscribe.size());

            quint16 port;
            int players_number;
            int players_max;

            stream >> gameService >> port >> players_number >> players_max;
            emit subscribe(socket->peerAddress(), gameService, port, players_number, players_max);
        } else if (buffer.startsWith(Message::unsubscribe)) {
            buffer.remove(0, Message::unsubscribe.size());

            quint16 port;

            stream >> gameService >> port;
            emit unsubscribe(socket->peerAddress(), gameService, port);
        } else if (buffer.startsWith(Message::listall)) {
            buffer.remove(0, Message::listall.size());
            stream >> gameService;

            QList<Game> games = server->games(gameService);

            foreach (Game game, games) {
                socket->write(game.server.toString().toUtf8());
                socket->write(" ");
                socket->write(QByteArray::number(game.port));
                socket->write(" ");
                socket->write(QByteArray::number(game.players_num));
                socket->write(" ");
                socket->write(QByteArray::number(game.players_max));
                socket->write("\n");
            }
            socket->write("\n");
        }

        socket->close();
    }
}
