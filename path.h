#ifndef PATH
#define PATH

#include <QList>
#include <QPoint>
class Game;
class Tile;

class Path{
public:
    Path(Game &game_, Tile &spawn_, Tile &dest_);

    Game &game;
    Tile &spawn;
    Tile &dest;
    Tile *current;
    QList<Tile*> path;
    QList<Tile*> open;
    QList<Tile*> closed;
    QList<Tile*> tiles;

};

#endif // PATH

