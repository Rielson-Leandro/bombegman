#ifndef MAPENTITY_H
#define MAPENTITY_H

#include <QObject>
#include <QPoint>

class World;

class MapEntity : public QObject
{
Q_OBJECT
public:
    explicit MapEntity(World *parent = 0);

    World *world();
    QPoint pos() const;

    virtual bool obstructive() const;
    quint8 getId() const;
    virtual void explode();


public slots:
    void setPos(const QPoint &p);

private:
    World *m_world;
    QPoint m_pos;
    quint8 id;
    // spritesSet
    // int currentSprite
};

inline QPoint MapEntity::pos() const
{
    return m_pos;
}

#endif // MAPENTITY_H
