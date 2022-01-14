#include "pillar.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>

Pillar::Pillar() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipa2Up.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipa2Down.png")))
{
    // manipulating the pillar height and width display, 60 is a magix number (space between the pillars)
    topPillar->setPos(QPointF(0, 0) - QPointF(topPillar->boundingRect().width() /2, // x-axis
                                             topPillar->boundingRect().height() + 30)); //y-axis

    bottomPillar->setPos(QPointF(0, 0) + QPointF(-bottomPillar->boundingRect().width() /2, // x-axis
                                             60)); //y-axis

    // add to group method allows treating multiple items as a single item (top and bottom pillar)
    addToGroup(topPillar);
    addToGroup(bottomPillar);

    // bounded random generator to randomise pipe position spawn
    yPos = QRandomGenerator::global()->bounded(150);
    int xPos = QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0, 0) + QPoint(260 + xPos, yPos));


    //                                  (target class, property name we want to animate, property parent for mem.management)
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xPos);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1250); // miliseconds

    connect(xAnimation, &QPropertyAnimation::finished,[=](){
        scene()->removeItem(this);
        delete this;
        });
    xAnimation->start();


}

Pillar::~Pillar()
{
    qDebug() << "Deleting pillar";
}

qreal Pillar::x() const
{
    return m_x;
}

void Pillar::setX(qreal newX)
{
    m_x = newX;
    setPos(QPointF(0, 0) + QPointF(newX, yPos));
}
