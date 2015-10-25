#ifndef TOWER
#define TOWER

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMouseEvent>

class Game;

class Tower: public QObject, public QGraphicsPixmapItem {
public:
    Tower(Game &game_, int x, int y, QGraphicsItem * parent=0);
private:
    Game &game;
};

#endif // TOWER

