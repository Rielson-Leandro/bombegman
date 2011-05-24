#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsObject>
#include <QTimer>

class PlayerItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit PlayerItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void setDir(char dir);

public slots:
    void startAnimated();
    void stopAnimated();

private slots:
    void onTimeout();

private:
    int dir;
    int state;
    QTimer timer;
    bool animate;
};

#endif // PLAYERITEM_H
