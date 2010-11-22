#ifndef MAP_H
#define MAP_H

#include <QObject>

class Map : public QObject
{
Q_OBJECT
public:
    explicit Map(QObject *parent = 0);

    void generateMap(/* parameters */);

signals:

public slots:

};

#endif // MAP_H
