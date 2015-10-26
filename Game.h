#ifndef GAME
#define GAME

#include "Wall.h"
#include "Tile.h"
#include "Enemy.h"
#include "Path.h"
#include <QGraphicsView>
#include "Tower.h"
#include <QObject>

class BuildWall;

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

    // tiles are indexed in int for easy sorting in QMap. We must use indexOfPoint(x,y) to get an index of a tile
    QMap<int,Tile*> tiles;

    // spawning entities
    void spawnBlueSlime(Tile &spawn, Tile &dest, Path &path);

    // getter setter
    int getTileSize();
    QMap<int,Tile*> getTiles();

    // pathing signal
    void generatePath();

    // tile indexing
    int indexOfPoint(int reload_bar_length, int y);

    // convert tile coordinate to scene coordinate
    int x_scene(int reload_bar_length);
    int y_scene(int y);

    Tower *tower;
    bool towerbuilt = false;

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

    // mouse input
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    // spawn dest
    Tile *spawn1;
    Tile *dest1;
    Tile *spawn2;
    Tile *dest2;

    BuildWall *buildwall;

    QGraphicsPixmapItem *smoke = nullptr;
    QTimer *smoke_timer;
    QTimer *reload_timer;
    QTimer *reload_bar_timer;
    QGraphicsRectItem *reload_bar;
    QGraphicsRectItem *base_reload_bar;
    int reload_bar_threshold = 0;

    int reload_bar_length = 2;
    bool redraw_reload_bar = false;

    QPixmap *cursor = nullptr;

    bool can_fire = true;

private slots:
    void animateSmoke();
    void reloadTimer();
    void reloadBarTimer();

};

#endif // GAME

