#ifndef GAME
#define GAME
#include <QGraphicsView>
#include "wall.h"


class Game: public QGraphicsView{
public:
    Game();

    QGraphicsPixmapItem * cursor;
    QGraphicsScene * scene;
    Wall * build_wall;

    // map and tile details
    int map_tiles_x; // number of tiles in x axis
    int map_tiles_y;
    int map_tile_size; // in pixels

    struct MapTile{
        QString sprite;
        int x;
        int y;

        // map coordinates in real pixels
        int x_real;
        int y_real;
    };

    struct AStarTile{
        bool walkable;
        int x;
        int y;

        // a*
        int heuristic;
    };

    // a* pathing
    QList<MapTile> open;
    QList<MapTile> closed;
    QList<AStarTile> a_star_tiles;

    // list of all tiles
    QList<MapTile> tiles;

    // list of path tiles
    QList<MapTile> path_tiles;

    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    // spawning entities
    void spawnBlueSlime(QPoint);

    // getter setter
    int getTileSize();

private:
    // game initializations
    void createMapTiles(QString filename);
    void createTilesOverlay(QString filename);
    void createScene();
    void setMapTile(int map_tiles_x, int map_tiles_y, int map_tile_size);

    // pathing
    void generatePath(QPoint spawn,QPoint dest);

    // convert tile coordinate to scene coordinate
    int x_scene(int x);
    int y_scene(int y);

public slots:
    void test();

};

#endif // GAME

