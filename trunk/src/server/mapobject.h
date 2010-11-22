#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>
#include <QPoint>

class MapObject : public QObject
{
Q_OBJECT
public:
    explicit MapObject(QObject *parent = 0);

    QPoint pos() const;

    virtual bool obstrutive() const;

signals:
    void posChanged();

public slots:
    void setPos(const QPoint &p);

protected:
    virtual void explode();

private:
    QPoint m_pos;
    // spritesSet
    // int currentSprite
};

inline QPoint MapObject::pos() const
{
    return m_pos;
}

#endif // MAPOBJECT_H
