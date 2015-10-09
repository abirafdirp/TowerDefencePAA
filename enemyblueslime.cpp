#include "enemyblueslime.h"
#include <QPixmap>
#include <QTimer>
#include "game.h"

extern Game * game;

BlueSlime::BlueSlime(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/enemy/assets/enemy/slimeBlue.png"));
}

void BlueSlime::move()
{
    setPos(x()+64,y());
}
