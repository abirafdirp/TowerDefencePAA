#ifndef PATH
#define PATH

#include <QList>
#include <QMap>
#include <QPoint>
class Game;
class Tile;

class Path{
public:
    Path(Game &game_, Tile &spawn_, Tile &dest_);

private:
    Game &game;
    Tile &spawn;
    Tile &dest;

    Tile *current;

    QList<Tile*> path;
    QMap<int,Tile*> open;
    QList<Tile*> closed;
    QList<Tile*> tiles;
    QList<Tile*> adjacent;

};

#endif // PATH

