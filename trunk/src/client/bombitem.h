#ifndef BOMBITEM_H
#define BOMBITEM_H

#include <QGraphicsObject>
#include <QTimer>

class BombItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit BombItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private slots:
    void onTimeout();

private:
    QTimer timer;
    int state;
};

#endif // BOMBITEM_H
