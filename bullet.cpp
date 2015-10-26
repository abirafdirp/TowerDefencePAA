// some of this is copy pasted from MeLikeyCode, to lazy to write

#include "bullet.h"
#include "Game.h"
#include <QPixmap>
#include <QTimer>
#include <QPointF>
#include <QTimer>
#include <QDebug>
#include <qmath.h> // qSin, qCos, qTan


Bullet::Bullet(Game &game_, QGraphicsItem *parent): game(game_), QObject(),QGraphicsPixmapItem(parent){
    // set graphics
    setPixmap(QPixmap(":/tank/assets/tank/bulletBlueSilver_outline.png"));


    // connect a timer to move()
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(20);
}

void Bullet::setTarget(QPoint target_)
{
    target = target_;
    target_check_timer = new QTimer();
    connect(target_check_timer,SIGNAL(timeout()),this,SLOT(targetCheck()));
    target_check_timer->start(20);
}


void Bullet::move(){
    int STEP_SIZE = 20;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

}

void Bullet::targetCheck()
{
    if (((this->pos().x() <= target.x() + 20) && (this->pos().x() >= target.x() - 20)) && ((this->pos().y() <= target.y() + 20) && (this->pos().y() >= target.y() - 20))) {
        disconnect(target_check_timer,SIGNAL(timeout()),this,SLOT(targetCheck()));

        explosion_animation_timer = new QTimer();
        connect(explosion_animation_timer,SIGNAL(timeout()),this,SLOT(explosionAnimation()));
        explosion_animation_timer->start(50);
        explosion = new QGraphicsPixmapItem(QPixmap(":/util/assets/util/regularExplosion02.png"));
        explosion->setPos(target);
        explosion->setOffset(-40,-45);
        game.scene->addItem(explosion);

        game.scene->removeItem(this);
    }
}

void Bullet::explosionAnimation()
{
    if (explosion->opacity() > 0) {
        explosion->setOpacity(explosion->opacity() - 0.05);
    }
    else {
        disconnect(explosion_animation_timer,SIGNAL(timeout()),this,SLOT(explosionAnimation()));
        delete explosion;
    }

}
