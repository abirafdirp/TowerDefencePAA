#ifndef TILE
#define TILE

#include <QGraphicsPixmapItem>
#include <QObject>

class Game;

class Tile: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tile(Game &game_, QPoint point, QGraphicsItem * parent=0);
    int getF();

    QPoint point;
    QPoint point_real;
    bool walkable;
    int force;
    int heuristic;

private:
    Game& game;

};

#endif // TILE

