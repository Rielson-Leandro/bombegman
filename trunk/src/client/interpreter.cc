#include "interpreter.h"

Interpreter::Interpreter(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    socket(socket)
{
}
