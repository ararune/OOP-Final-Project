#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setUpPillarTimer();

}

void Scene::addBird()
{
    bird = new Bird(QPixmap(":/images/yellowbird-upflap.png"));
    addItem(bird);
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, [=](){
        Pillar * pillarItem = new Pillar();

        addItem(pillarItem);
    });
    pillarTimer->start(1000); // create new pillar each second
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        bird->shootUp();
    }
    QGraphicsScene::mousePressEvent(event);
}
