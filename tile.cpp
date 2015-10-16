#include "Tile.h"
#include "Game.h"
#include "MyApplication.h"
#include <QPoint>
#include <QPixmap>
#include <QDebug>
#include <QPainter>


Tile::Tile(Game &game_, QPoint point, QGraphicsItem *parent) : game(game_)
{
    this->point = point;
    this->point_real = point * game.getTileSize();
    setZValue(0);
}

int Tile::getF()
{
    return g + h;
}
