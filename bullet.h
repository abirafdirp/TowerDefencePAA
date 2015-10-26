// copy pasted from MeLikeyCode, to lazy to write

#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Game;

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(Game &game_, QGraphicsItem * parent=0);
    void setTarget(const QPoint target_);
private:
    QTimer *target_check_timer;
    QTimer *explosion_animation_timer;
    QPoint target;
    Game &game;
    QGraphicsPixmapItem *explosion;
public slots:
    void move();
private slots:
    void targetCheck();
    void explosionAnimation();
};

#endif // BULLET_H

