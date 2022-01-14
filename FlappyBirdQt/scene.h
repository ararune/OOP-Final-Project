#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "pillar.h"
#include "bird.h"
#include <QTimer>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void addBird();

signals:
private:
    void setUpPillarTimer(); // method to set a timer that will add pillars in given interval


    QTimer * pillarTimer;
    Bird * bird;


    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
