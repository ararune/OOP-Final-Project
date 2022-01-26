#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false), score(0), highestScore(0)
{
    setUpPillarTimer();
}

void Scene::addBird()
{
    bird = new Bird(QPixmap(":/images/yellowbird-upflap.png"));
    addItem(bird);
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;
    if(score > highestScore){
        highestScore = score;
    }

}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/gameover.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0, 0) - QPointF(gameOverPix->boundingRect().width()/2,
                                                gameOverPix->boundingRect().height()/2));

    scoreText = new QGraphicsTextItem();
    QString htmlString = "<p> Score : " + QString::number(score) + " </p>"
            +  "<p> Best Score : " + QString::number(highestScore) + "</p>";

    QFont mFont("Consolas", 30, QFont::Bold);
    scoreText->setHtml(htmlString);
    scoreText->setFont(mFont);
    scoreText->setDefaultTextColor(Qt::green);
    addItem(scoreText);

    scoreText->setPos(QPointF(0, 0) - QPointF(scoreText->boundingRect().width()/2,
                                              scoreText->boundingRect().height()/2));
}

void Scene::hideGameOverGraphics()
{
    if (gameOverPix){
        removeItem(gameOverPix) ;
        delete gameOverPix;
        gameOverPix= nullptr;

    }

    if (scoreText) {
        removeItem(scoreText) ;
        delete scoreText;
        scoreText = nullptr;

    }
}
// loop through all the items in the scene
// with each iteration cast item to Pillar

void Scene::cleanPillars()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem * item, sceneItems){
        Pillar * pillar = dynamic_cast<Pillar *>(item);
        if(pillar){
            removeItem(pillar);
            delete pillar;
        }
    }
}

/*void Scene::playGame()
{
    bird->startFlying();
    if(!pillarTimer->isActive()){    // isActive returns true when timer has started
        pillarTimer->start(1000);   // start timer if it hasn't already
   }
}*/
void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, [=](){
        Pillar * pillarItem = new Pillar();
        connect(pillarItem,&Pillar::collideFail,[=](){
            pillarTimer->stop();
            freezeScene();
            setGameOn(false);
            //showGameOverGraphics();
        });

        addItem(pillarItem);
    });
    //pillarTimer->start(1000); // create new pillar each second
}

void Scene::freezeScene()
{
    bird->freezeBird();
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem * item, sceneItems){
        Pillar * pillar = dynamic_cast<Pillar *>(item);
        if(pillar){
            pillar->freezePillars();    // if cast successful, freeze pillars
        }
    }

}


void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        if(gameOn){
            bird->shootUp();
        }
    }

    if(event->key() == Qt::Key_Escape){
        bird->startFlying();
        if(!pillarTimer->isActive()){    // isActive returns true when timer has started
            cleanPillars();
            setGameOn(true);
            //hideGameOverGraphics();
            pillarTimer->start(1000);   // start timer if it hasn't already
        }
    }
    QGraphicsScene::keyPressEvent(event);

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}
