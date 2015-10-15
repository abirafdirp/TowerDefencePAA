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

    // list of all tiles
    QList<Tile*> tiles;

    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    // spawning entities
    void spawnBlueSlime(QPoint spawn, QPoint dest);

    // getter setter
    int getTileSize();
    QList<Tile*> getTiles();

private:
    // game initializations
    void createMapTiles(QString filename);
    void createScene();
    void setMapTile(int map_width_in_tiles, int map_height_in_tiles, int map_tile_size);

    // convert tile coordinate to scene coordinate
    int x_scene(int x);
    int y_scene(int y);

    // qlist holding the tiles is 1d, so we must implement index function
    int tileIndex(int x, int y);

    // debugging
    void drawTilesOverlay(QString filename);
    void drawTilesDebug();

};

#endif // GAME

