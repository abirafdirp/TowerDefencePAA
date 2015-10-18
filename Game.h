#ifndef GAME
#define GAME

#include "Wall.h"
#include "Tile.h"
#include "Enemy.h"
#include <QGraphicsView>


class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();

    QGraphicsScene * scene;
    Wall * build_wall;

    // map and tile details
    int map_width_in_tiles; // number of tiles in x axis
    int map_height_in_tiles;
    int map_tile_size; // in pixels

    // tiles are indexed in int for easy sorting in QMap. We must use tileCoordinate(x.y) to get an index of a tile
    QMap<int,Tile*> tiles;

    // spawning entities
    void spawnBlueSlime(QPoint spawn, QPoint dest);

    // getter setter
    int getTileSize();
    QMap<int,Tile*> getTiles();

    // pathing signal
    void generatePath();

    // tile indexing
    int indexOfPoint(int x, int y);

    // convert tile coordinate to scene coordinate
    int x_scene(int x);
    int y_scene(int y);

private:

    // game initializations
    void createMapTiles(QString filename);
    void createScene();
    void setMapTile(int map_width_in_tiles, int map_height_in_tiles, int map_tile_size_);

    // debugging
    void drawTilesOverlay(QString filename);
    void drawTilesPoint();

    //
    void printAllTiles();

};

#endif // GAME

