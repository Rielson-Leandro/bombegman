#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class QTcpSocket;

class Player : public QObject
{
Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

signals:

public slots:

private:
    QTcpSocket *socket;
};

#endif // PLAYER_H
