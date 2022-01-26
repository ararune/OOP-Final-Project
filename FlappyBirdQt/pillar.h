#ifndef PILLAR_H
#define PILLAR_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Pillar : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)


public:
    explicit Pillar();
    ~Pillar();

    qreal x() const;
    void setX(qreal newX);
    void freezePillars();

signals:
    void collideFail(); // game stop upon collision
private:
    bool isColliding();
    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;
    QPropertyAnimation  * xAnimation;

    int yPos;
    qreal m_x;
    bool isPastBird;
};

#endif // PILLAR_H
