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
    void playGame();
    bool getGameOn() const;
    void setGameOn(bool value);
    void incrementScore();

signals:
private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();      // remove pillars from previous session on start
    void setUpPillarTimer(); // method to set a timer that will add pillars in given interval
    void freezeScene();     // upon collision, stop the bird and pillars
    bool gameOn;
    QTimer * pillarTimer;
    Bird * bird;

    int score;
    int highestScore;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreText;
    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SCENE_H
