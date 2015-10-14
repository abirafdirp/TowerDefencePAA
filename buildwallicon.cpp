#include "BuildWallIcon.h"
#include "Game.h"

extern Game * game;

BuildWallIcon::BuildWallIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/wall/assets/wall/brick_red.png"));
}

void BuildWallIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /*if (!game->build_wall){
        game->build_wall = new Wall();
        game->setCursor(":/wall/assets/wall/brick_red.png");
    }*/
}
