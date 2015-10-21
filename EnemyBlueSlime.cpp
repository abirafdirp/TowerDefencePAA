#include "EnemyBlueSlime.h"
#include <QPixmap>
#include <QTimer>
#include "Path.h"
#include "Game.h"
#include "Tile.h"

BlueSlime::BlueSlime(Path &path_, QGraphicsItem *parent) : path(path_)
{
    setPixmap(QPixmap(":/enemy/assets/enemy/slimeBlue.png"));
}

void BlueSlime::move()
{
    foreach(Tile *tile, path.path){
        setPos(tile->x(),tile->y());
    }
}
