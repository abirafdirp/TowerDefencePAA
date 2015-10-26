#ifndef PATH
#define PATH

#include <QList>
#include <QMap>
#include <QPoint>
class Game;
class Tile;

class Path{
public:
    QList<Tile*> path;
    Path(Game &game_, Tile &spawn_, Tile &dest_);
    QList<Tile*> getPath();
    Game &game;

    bool destfound = false;

private:
    // we want to redraw everything after a tile gets updated,
    int update_z_index = 150;
    Tile &spawn;
    Tile &dest;

    Tile *current;

    // QMap is sorted based on its keys
    QMap<int,Tile*> open; // F as key
    QMap<int,Tile*> closed; // index as key
    QMap<int,Tile*> tiles; // index as key

    // pathing debug
    void drawTileDebug(Tile &tile);
    void printPath();
    void printOpen();

    // tiles are inside maps
    bool openContains(Tile &tile);
    bool closedContains(Tile &tile);


    void reconstructPath();

};

#endif // PATH

