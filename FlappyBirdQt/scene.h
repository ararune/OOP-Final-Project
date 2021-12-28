#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "pillar.h"
#include <QTimer>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

signals:
private:
    void setUpPillarTimer(); // method to set a timer that will add pillars in given interval


    QTimer * pillarTimer;

};

#endif // SCENE_H
