#ifndef MAPENTITY_H
#define MAPENTITY_H

#include <QObject>
#include <QPoint>

class MapEntity : public QObject
{
Q_OBJECT
public:
    explicit MapEntity(QObject *parent = 0);

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

inline QPoint MapEntity::pos() const
{
    return m_pos;
}

#endif // MAPENTITY_H
