#include "EnemyBlueSlime.h"
#include <QPixmap>
#include <QTimer>
#include "Path.h"
#include "Game.h"
#include "Tile.h"
#include <QMessageBox>

BlueSlime::BlueSlime(Game &game_, Path &path_, QGraphicsItem *parent) : game(game_), path(path_)
{
    setPixmap(QPixmap(":/enemy/assets/enemy/alienBeige_walk1.png"));
    lenindex = path.path.length() - 1;
    setZValue(1);
    setScale(0.8);
    setOffset(10,10);
}

void BlueSlime::move()
{
    animation_index += 1;
    if (animation_index % 2 == 1){
        setPixmap(QPixmap(":/enemy/assets/enemy/alienBeige_walk2.png"));
    }
    else {
        setPixmap(QPixmap(":/enemy/assets/enemy/alienBeige_walk1.png"));
    }
    if (lenindex >= 0){
        setPos(path.path.at(lenindex)->x(),path.path.at(lenindex)->y());
        lenindex--;
    }
    if (lenindex == -1) {
        QMessageBox msgBox;
        msgBox.setText("Anda kalah! Skor anda adalah");
        msgBox.exec();
        game.restartScene();
    }

}
