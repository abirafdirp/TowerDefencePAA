#include "tower.h"
#include <QPixmap>


Tower::Tower(QGraphicsItem *parent)
{
    // set the graphics
    setPixmap(QPixmap(":/wall/assets/wall/brick_red.png"));
}
