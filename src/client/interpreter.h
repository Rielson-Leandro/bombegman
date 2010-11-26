#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>

class QTcpSocket;

class Interpreter : public QObject
{
Q_OBJECT
public:
    explicit Interpreter(QTcpSocket *socket, QObject *parent = 0);

signals:

public slots:

private:
    QTcpSocket *socket;
};

#endif // INTERPRETER_H
