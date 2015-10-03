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
    int map_tile_width;
    int Map_tile_height;
    int map_tiles_x;
    int map_tiles_y;
    int map_tile_size; // in pixels

    struct MapTile{
        bool walkable;
        QString sprite;
    };

    void createMapTiles(QString filename);
    void createTilesOverlay(QString filename);
    void createScene();
    void setMapTile(int map_tiles_x, int map_tiles_y, int map_tile_size);
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

};

#endif // GAME

