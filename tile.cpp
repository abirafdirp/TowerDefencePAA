#include "Tile.h"
#include "Game.h"
#include "MyApplication.h"
#include <QPoint>
#include <QPixmap>
#include <QDebug>


Tile::Tile(Game &game_, QGraphicsItem *parent) : game(game_)
{

}

void Tile::setPoint(QPoint point)
{
    this->point = point;
}

void Tile::setPointReal(QPoint point)
{
    this->point = point * game.getTileSize();
}
