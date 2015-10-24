#include "EnemyBlueSlime.h"
#include <QPixmap>
#include <QTimer>
#include "Path.h"
#include "Game.h"
#include "Tile.h"

BlueSlime::BlueSlime(Path &path_, QGraphicsItem *parent) : path(path_)
{
    setPixmap(QPixmap(":/enemy/assets/enemy/slimeBlue.png"));
    lenindex = path.path.length() - 1;
}

void BlueSlime::move()
{
    if (lenindex >= 0){
        setPos(path.path.at(lenindex)->x(),path.path.at(lenindex)->y());
        lenindex--;
    }
    if (lenindex == -1) {

        delete this;
    }

}
