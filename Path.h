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
    // we want to redraw everything after a tile gets updated. this is a bad behaviour
    int update_z_index = 102;
    Game &game;
    Tile &spawn;
    Tile &dest;

    Tile *current;

    QList<Tile*> path;

    // QMap is sorted based on its keys
    QMap<int,Tile*> open; // F as key
    QMap<int,Tile*> closed; // index as key
    QMap<int,Tile*> tiles; // index as key
    // QMap<int,Tile*> adjacent; // F as key

    void drawTileFGH(Tile &tile);
    void drawTileParent(Tile &tile, Tile &parent);
    void updateTileDebug(Tile &tile);
    bool openContains(Tile &tile);
    bool closedContains(Tile &tile);

    void printOpen();

};

#endif // PATH

