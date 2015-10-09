#include "game.h"
#include "tower.h"
#include "enemyblueslime.h"
#include "wall.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>
#include <QObject>
#include <QDebug>

Game::Game()
{
    build_wall = nullptr;
    cursor = nullptr;
    setMouseTracking(true);
    setMapTile(19,10,64);
    createScene();
    createMapTiles(":/floor/assets/floor/dirt.png");
    createTilesOverlay(":/util/assets/util/sTrackBorder_0.png");
    setCursor(":/wall/assets/wall/brick_red.png");
    TilePoint spawn1 = addTilePoint(12,5);
    TilePoint dest1 = addTilePoint(19,5);
    spawnBlueSlime(spawn1);
}

void Game::createMapTiles(QString filename)
{
    QList<MapTile> tiles[map_tiles_x][map_tiles_y];
    for(int i = 0; i < map_tiles_x; i++){
        for(int n = 0; n < map_tiles_y; n++){
            MapTile tile;
            tile.walkable = true;
            tile.x = i;
            tile.y = n;
            tile.x_real = this->map_tile_size * i;
            tile.y_real = this->map_tile_size * n;

            tiles[i][n].append(tile);

            // set the floor sprite
            QGraphicsPixmapItem * floor = new QGraphicsPixmapItem();
            floor->setPixmap(QPixmap(filename));
            floor->setScale(0.5);
            floor->setZValue(0);
            floor->setPos(i*64,n*64);
            scene->addItem(floor);
        }
    }


}

void Game::createTilesOverlay(QString filename)
{
    for(int i = 0; i < map_tiles_x; i++){
        for(int n = 0; n < map_tiles_y; n++){

            // set the floor overlay
            QGraphicsPixmapItem * overlay = new QGraphicsPixmapItem();
            overlay->setPixmap(QPixmap(filename));
            overlay->setScale(1);
            overlay->setZValue(100);
            overlay->setPos(i*64,n*64);
            scene->addItem(overlay);
        }
    }


}

void Game::createScene()
{
    int scene_height = map_tiles_y * map_tile_size;
    int scene_width = map_tiles_x * map_tile_size;

    // create a scene
    scene = new QGraphicsScene(this);

    // set the scene
    setScene(scene);
    scene->setSceneRect(0,0,scene_width,scene_height);

    // can someone explain this? the size is not the same as the scene
    setFixedSize(scene_width+2,scene_height+2);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::setMapTile(int map_tiles_x, int map_tiles_y, int map_tile_size)
{
    this->map_tiles_x = map_tiles_x;
    this->map_tiles_y = map_tiles_y;
    this->map_tile_size = map_tile_size;
}

Game::TilePoint Game::addTilePoint(int x, int y)
{
    TilePoint spawn;
    spawn.x = x;
    spawn.y = y;
    return spawn;
}

void Game::generatePath(Game::TilePoint spawn, Game::TilePoint dest)
{
    for(int i = 0; i < map_tiles_x; i++){
        for(int n = 0; n < map_tiles_y; n++){

            // set the floor overlay
            AStarTile tile;
            tile.x = i;
            tile.y = n;
            tile.walkable = true;
            a_star_tiles.append();
        }
    }
}

void Game::setCursor(QString filename)
{
    if (cursor){
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    cursor->setScale(0.5);
    cursor->setZValue(1);
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent * event)
{
    if (cursor){
        cursor->setPos(event->pos());
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (build_wall){
        scene->addItem(build_wall);
        build_wall->setPos(event->pos());
        cursor = nullptr;
        build_wall = nullptr;
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}

void Game::spawnBlueSlime(TilePoint tile_point)
{
    BlueSlime * blueslime = new BlueSlime();
    scene->addItem(blueslime);
    blueslime->setPos(x_scene(tile_point.x),y_scene(tile_point.y));
    QTimer * fps = new QTimer(this);
    connect(fps,SIGNAL(timeout()),blueslime,SLOT(move()));
    fps->start(1000);
}

void Game::generatePath()
{

}

int Game::x_scene(int x)
{
    return x * map_tile_size;
}

int Game::y_scene(int y)
{
    return y * map_tile_size;
}
void Game::test()
{
    qDebug() << "fuck2";
}

