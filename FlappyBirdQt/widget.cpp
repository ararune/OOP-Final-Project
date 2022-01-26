#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include "scene.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-250, -300, 500, 600);

    QGraphicsPixmapItem * background = new QGraphicsPixmapItem(QPixmap(":/images/glowingEdges2.png"));
    scene->addItem(background);
    background->setPos(QPointF(0, 0) - QPointF(background->boundingRect().width()/2,
                                            background->boundingRect().height()/2));


    scene->addLine(-400, 0, 400, 0, QPen(Qt::red));
    scene->addLine(0, -400, 0, 400, QPen(Qt::red));



    //Pillar *pillar = new Pillar();
    //scene->addItem(pillar);

    ui->graphicsView->setScene(scene);

    scene->addBird();
}

Widget::~Widget()
{
    delete ui;
}


