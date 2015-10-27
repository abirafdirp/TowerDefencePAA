#ifndef GAME
#define GAME

#include "Wall.h"
#include "Tile.h"
#include "Enemy.h"
#include "Path.h"
#include <QGraphicsView>
#include "Tower.h"
#include <QObject>
#include <QGraphicsTextItem>

class BuildWall;

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    QGraphicsTextItem * score_text;

    int score = 0;

    QGraphicsScene * scene;
    Wall * build_wall;

    // map and tile details
    int map_width_in_tiles; // number of tiles in x axis
    int map_height_in_tiles;
    int map_tile_size; // in pixels

    // tiles are indexed in int for easy sorting in QMap. We must use indexOfPoint(x,y) to get an index of a tile
    QMap<int,Tile*> tiles;

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

    // spawn dest
    Tile *spawn1;
    Tile *dest1;
    Tile *spawn2;
    Tile *dest2;

    void restartScene();

    QTimer *spawner_timer;
    int increase_spawner = 0;

private:

    Path *path;

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

    BuildWall *buildwall;

    QGraphicsPixmapItem *smoke = nullptr;
    QTimer *smoke_timer;
    QTimer *reload_timer;
    QTimer *reload_bar_timer;
    QGraphicsRectItem *reload_bar;
    QGraphicsRectItem *reload_bar_placeholder;
    QGraphicsRectItem *base_reload_bar;
    int reload_bar_threshold = 0;

    int reload_bar_length = 2;
    bool redraw_reload_bar = false;

    QPixmap *cursor = nullptr;

    bool can_fire = true;

//    void keyPressEvent(QKeyEvent *ev);

private slots:
    void animateSmoke();
    void reloadTimer();
    void reloadBarTimer();

    // spawning entities, must set path member variable
    void spawnBlueSlime();

};

#endif // GAME

