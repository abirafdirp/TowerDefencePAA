#include "tile.h"
#include "game.h"
#include <QPoint>

extern Game * game;

Tile::Tile(QGraphicsItem * parent)
{

}

void Tile::setPoint(QPoint point)
{
    this->point = point;
}

void Tile::setPointReal(QPoint point)
{
    this->point_real = point * game->getTileSize();
}
