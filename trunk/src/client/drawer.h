#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include "mapentity.h"

class QGraphicsScene;
class QPushButton;
class QGraphicsProxyWidget;

class Drawer : public QObject
{
Q_OBJECT
public:
    explicit Drawer(QGraphicsScene *scene, QObject *parent = 0);
    ~Drawer();

signals:
    void removeButtonClicked();

public slots:
    void requestMovement(MapEntity entity, QPoint newPos);
    void requestNewEntity(MapEntity entity, QPoint pos);
    void requestHavoc(MapEntity entity);

    void addReadyButton();
    void removeReadyButton();

private:
    QGraphicsScene *scene;
    bool sceneHasReadyButton;
    QPushButton *button;
    QGraphicsProxyWidget *buttonItem;
};

#endif // DRAWER_H
