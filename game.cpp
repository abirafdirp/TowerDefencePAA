#include "game.h"
#include "tower.h"
#include "wall.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMouseEvent>

Game::Game()
{
    build_wall = nullptr;
    cursor = nullptr;
    setMouseTracking(true);
}

void Game::createMapTiles(QString filename)
{
    MapTile tiles[map_tiles_x][map_tiles_y];
    for(int i = 0; i < map_tiles_x; i++){
        for(int n = 0; n < map_tiles_y; n++){

            // floors are walkable
            tiles[i][n].walkable = true;

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

