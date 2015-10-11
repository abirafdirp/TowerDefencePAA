#include "tile.h"
#include "game.h"

extern Game * game;

Tile::Tile(QGraphicsItem * parent)
{

}

void Tile::setX(int x)
{
    this->x = x;
}

void Tile::setY(int y)
{
    this->y = y;
}

void Tile::setXReal(int x)
{
    this->x_real = x * game->getTileSize();
}

void Tile::setYReal(int y)
{
    this->y_real = y * game->getTileSize();
}
