#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>


class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Bird(QPixmap pixmap); //default pixmap that shows up the first time it's added to the scene

    qreal rotation() const;
    void setRotation(qreal newRotation);

    qreal y() const;
    void setY(qreal newY);

    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);
    void shootUp();
    void fallAfterJump();


signals:

private:
    enum WingPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();

    WingPosition wingPosition;
    bool wingDirection; // 0 -> down, 1 -> up

    qreal m_rotation;
    qreal m_y;

    QPropertyAnimation *rotationAnimation;
    QPropertyAnimation *yAnimation;

    qreal groundPosition;

};

#endif // BIRD_H
