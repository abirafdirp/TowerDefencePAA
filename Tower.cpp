#include "Tower.h"
#include <QPixmap>
#include "Game.h"
#include <QDebug>


Tower::Tower(Game &game_, int x, int y, QGraphicsItem *parent) : game(game_)
{
    // set the graphics
    setPixmap(QPixmap(":/tank/assets/tank/barrelBeige_outline.png"));
    QGraphicsPixmapItem *tank = new QGraphicsPixmapItem(QPixmap(":/tank/assets/tank/tankBeige_outline.png"));
    tank->setPos(x,y);
    tank->setTransformOriginPoint(tank->boundingRect().width() / 2, tank->boundingRect().height() / 2);
    tank->setRotation(270);
    this->setZValue(100);
    this->setTransformOriginPoint(9, 42);
    this->setPos(tank->x() + 23, tank->y() - 12);
    this->setRotation(270);
    game.scene->addItem(this);
    game.scene->addItem(tank);

}

