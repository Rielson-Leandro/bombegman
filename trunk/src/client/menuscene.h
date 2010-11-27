#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QHostAddress>

class ConnectDialog;

class MenuScene : public QGraphicsScene
{
Q_OBJECT
public:
    explicit MenuScene(QObject *parent = 0);

signals:
    void connectionRequested(QHostAddress, quint16);

private slots:
    void onConnectionRequested();

private:
    ConnectDialog *connectionDialog;
};

#endif // MENUSCENE_H
