#include "EnemyBlueSlime.h"
#include "MyApplication.h"
#include <QPixmap>
#include <QTimer>
#include "Path.h"
#include "Game.h"
#include "Tile.h"
#include "QDebug"
#include <QMessageBox>
#include <QGraphicsTextItem>

BlueSlime::BlueSlime(Game &game_, Path &path_, QGraphicsItem *parent) : game(game_), path(path_)
{
    setPixmap(QPixmap(":/enemy/assets/enemy/alienBeige_walk1.png"));
    lenindex = path.path.length() - 1;
    setZValue(1);
    setScale(0.8);
    setOffset(10,10);

    game.scene->addItem(this);
    this->setPos(game.x_scene(game.spawn1->point.x()),game.y_scene(game.spawn1->point.y()));
    QTimer *fps = new QTimer(this);
    connect(fps,SIGNAL(timeout()),this,SLOT(move()));
    fps->start(1000);
}

void BlueSlime::startSpawner()
{
//    spawner_timer = new QTimer();
//    connect(spawner_timer,SIGNAL(timeout()),this,SLOT(spawner()));
    //    spawner_timer->start(3000);
}

void BlueSlime::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape) {
        game.restartScene();
    }
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
    if ((lenindex == -1) && (this->isVisible() == true)) {
        foreach(QGraphicsItem *item, game.scene->items()){
            if (item->zValue() == 1){
                if(item != this){
                    delete item;
                }
            }
        }
        disconnect(game.spawner_timer,SIGNAL(timeout()),&game,SLOT(spawnBlueSlime()));
        QGraphicsPixmapItem *skor = new QGraphicsPixmapItem(QPixmap(":/menu/assets/menu/score copy.png"));
        game.scene->addItem(skor);

        QGraphicsTextItem *skor_text = new QGraphicsTextItem(QString("%1").arg(game.score));
        skor_text->setPos(586,170);
        skor_text->setZValue(99999);
        skor_text->setScale(4);
        game.scene->addItem(skor_text);

        grabKeyboard();
    }

}

void BlueSlime::spawner()
{
    BlueSlime *slime = new BlueSlime(this->game,this->path);
    game.scene->addItem(slime);
}
