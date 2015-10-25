#ifndef TILE
#define TILE

#include <QGraphicsPixmapItem>
#include <QObject>

class Game;

class Tile: public QGraphicsPixmapItem {
public:
    Tile(Game &game_, QPoint point, QGraphicsItem * parent=0);
    int processF();

    QPoint point;
    QPoint point_real;
    bool walkable;
    int h;
    int g;
    int f;
    Tile *parent_tile;
private:
    Game& game;


};

#endif // TILE

