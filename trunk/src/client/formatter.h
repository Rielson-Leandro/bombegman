#ifndef FORMATTER_H
#define FORMATTER_H

#include <QObject>

class QTcpSocket;

class Formatter : public QObject
{
Q_OBJECT
public:
    explicit Formatter(QTcpSocket *socket, QObject *parent = 0);

signals:

public slots:

private:
    QTcpSocket *socket;
};

#endif // FORMATTER_H
