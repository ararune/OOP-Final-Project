#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setUpPillarTimer();
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
