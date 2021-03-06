#include "Tile.h"
#include "Game.h"
#include <QPoint>
#include <QPixmap>
#include <QDebug>
#include <QPainter>


Tile::Tile(Game &game_, QPoint point, QGraphicsItem *parent) : game(game_), QGraphicsPixmapItem(parent)
{
    this->point = point;
    this->point_real = point * game.getTileSize();
    setZValue(0);
}

int Tile::processF()
{
    return g + h;
}


