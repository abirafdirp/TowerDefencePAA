#include "Tile.h"
#include "Game.h"
#include "MyApplication.h"
#include <QPoint>
#include <QPixmap>



Tile::Tile(QGraphicsItem *parent)
{
}

void Tile::setPoint(QPoint point)
{
    this->point = point;
}

void Tile::setPointReal(QPoint point)
{
    //this->point_real = point * Game::getInstance().getTileSize();
}
