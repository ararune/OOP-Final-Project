#include "bird.h"
#include <QTimer>
#include <QGraphicsScene>

Bird::Bird(QPixmap pixmap) :
    wingPosition(WingPosition::Up),  // wing position up by default
    wingDirection(0)                // wing direction down by default
{
    setPixmap(pixmap);
    QTimer * birdWingsTimer = new QTimer(this);
    connect(birdWingsTimer, &QTimer::timeout, [=](){
        updatePixmap();
    });

    birdWingsTimer->start(80);

    groundPosition = scenePos().y() + 370;  // 370 is a magic number, tweakable

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);      // 1 second
    yAnimation->start();

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
    rotateTo(90, 1200, QEasingCurve::InQuad);       // 90 -> angle, 1.2 seconds duration, easing curve


}

void Bird::updatePixmap()
{
    if(wingPosition == WingPosition::Middle){
        if(wingDirection){
            // UP
            setPixmap(QPixmap(":/images/yellowbird-upflap.png"));
            wingPosition = WingPosition::Up;
            wingDirection = 0;  // flip the wing direction
        }
        else{
            //DOWN
            setPixmap(QPixmap(":/images/yellowbird-downflap.png"));
            wingPosition = WingPosition::Down;
            wingDirection = 1;  // flip the wing direction
        }
    }
    else{
        setPixmap(QPixmap(":/images/yellowbird-midflap.png"));
        wingPosition = WingPosition::Middle;
    }
}

qreal Bird::rotation() const
{
    return m_rotation;
}

void Bird::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF c = boundingRect().center();        // c-> center point of the bird

    QTransform t;
    t.translate(c.x(), c.y());                  // translate to the center of the bird
    t.rotate(rotation);
    t.translate(-c.x(), -c.y());                // come back to wherever we were before transform
    setTransform(t);

}

qreal Bird::y() const
{
    return m_y;
}

void Bird::setY(qreal y)    //make the bird fall down
{
    moveBy(0, y-m_y);
    m_y = y;
}

void Bird::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);      // 1.2 seconds

    rotationAnimation->start();
}

void Bird::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal currPosY = y();
    yAnimation->setStartValue(currPosY);
    yAnimation->setEndValue(currPosY - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);

    connect(yAnimation, &QPropertyAnimation::finished, [=](){
        fallAfterJump();

    });
    yAnimation->start();

    rotateTo(-20, 200, QEasingCurve::OutCubic); // tilt to top
}

void Bird::fallAfterJump()
{
    if(y() < groundPosition){
        rotationAnimation->stop();
        //yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200);
        yAnimation->start();

        rotateTo(90, 1100, QEasingCurve::InCubic);

    }



}
