#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>

class QGraphicsScene;

class Drawer : public QObject
{
Q_OBJECT
public:
    explicit Drawer(QGraphicsScene *scene, QObject *parent = 0);

signals:

public slots:

private:
    QGraphicsScene *scene;
};

#endif // DRAWER_H
