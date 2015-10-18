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

    QGraphicsPixmapItem * cursor;
    QGraphicsScene * scene;
    Wall * build_wall;

    // map and tile details
    int map_width_in_tiles; // number of tiles in x axis
    int map_height_in_tiles;
    int map_tile_size; // in pixels

    // tiles are indexed in int for easy sorting in QMap. We must use tileCoordinate(x.y) to get an index of a tile
    QMap<int,Tile*> tiles;

    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    // spawning entities
    void spawnBlueSlime(QPoint spawn, QPoint dest);

    // getter setter
    int getTileSize();
    QMap<int,Tile*> getTiles();

    // pathing signal
    void generatePath();

    // pathing debug
    void drawOpenRect(int x, int y);
    void drawClosedRect(int x, int y);

    // tile indexing
    int indexOfPoint(int x, int y);

    // convert tile coordinate to scene coordinate
    int x_scene(int x);
    int y_scene(int y);

private:
    int update_z_index = 100;

    // game initializations
    void createMapTiles(QString filename);
    void createScene();
    void setMapTile(int map_width_in_tiles, int map_height_in_tiles, int map_tile_size);

    // debugging
    void drawTilesOverlay(QString filename);
    void drawTilesPoint();

    //
    void printAllTiles();

};

#endif // GAME

