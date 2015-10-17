#include "Game.h"
#include "Tower.h"
#include "EnemyBlueSlime.h"
#include "Wall.h"
#include "Tile.h"
#include "Path.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QPoint>
#include <QMap>
#include <QMapIterator>
#include <QGraphicsRectItem>
#include <QBrush>

Game::Game()
{
    build_wall = nullptr;
    cursor = nullptr;
    setMouseTracking(true);
    setMapTile(20,10,64);
    createScene();
    createMapTiles(":/floor/assets/floor/dirt.png");
    drawTilesOverlay(":/util/assets/util/sTrackBorder_0.png");
    //drawTilesDebug();
    //printAllTiles();
    setCursor(":/wall/assets/wall/brick_red.png");
    QPoint spawn11 = QPoint(1,5);
    QPoint dest11 = QPoint(1,5);
}

void Game::generatePath() {
    Tile *spawn1 = tiles.value(indexOfPoint(1,5));
    Tile *dest1 = tiles.value(indexOfPoint(11,5));
    Path *path = new Path(*this,*spawn1,*dest1);
}

void Game::createMapTiles(QString filename)
{
    for(int x = 0; x < map_width_in_tiles; x++){
        for(int y = 0; y < map_height_in_tiles; y++){
            // set the floor sprite
            Tile * tile = new Tile(*this, QPoint(x,y));
            tile->setPixmap(QPixmap(filename));
            tile->setScale(0.5);
            tile->setPos(x_scene(x),y_scene(y));
            tile->walkable = true;
            if ((y == 4) || (y == 5) || (y == 6) || (y == 7) || (y == 3)){
                tile->setPixmap(QPixmap(":/wall/assets/wall/brick_red.png"));
                tile->walkable = false;
            }
            if (x % 2 == 1){
                tile->setPixmap(QPixmap(filename));
                tile->walkable = true;
            }


            this->tiles.insert(indexOfPoint(x,y),tile);
            scene->addItem(tile);
        }
    }


}

void Game::createScene()
{
    int scene_height = map_height_in_tiles * map_tile_size;
    int scene_width = map_width_in_tiles * map_tile_size;

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
    this->map_width_in_tiles = map_tiles_x;
    this->map_height_in_tiles = map_tiles_y;
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

void Game::spawnBlueSlime(QPoint spawn, QPoint dest)
{
    BlueSlime * blueslime = new BlueSlime();
    scene->addItem(blueslime);
    blueslime->setPos(x_scene(spawn.x()),y_scene(spawn.y()));
    QTimer *fps = new QTimer(this);
    connect(fps,SIGNAL(timeout()),blueslime,SLOT(move()));
    fps->start(1000);
}

int Game::getTileSize()
{
    return this->map_tile_size;
}

QMap<int,Tile*> Game::getTiles()
{
    return this->tiles;
}

int Game::x_scene(int x)
{
    return x * this->map_tile_size;
}

int Game::y_scene(int y)
{
    return y * this->map_tile_size;
}

int Game::indexOfPoint(int x, int y)
{
    return x + map_width_in_tiles * y;
}
void Game::drawTilesOverlay(QString filename)
{
    for(int i = 0; i < map_width_in_tiles; i++){
        for(int n = 0; n < map_height_in_tiles; n++){

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

void Game::drawTilesDebug()
{
    QMapIterator<int,Tile*> tile(tiles);
    while (tile.hasNext()){
        tile.next();
        QGraphicsTextItem *text = new QGraphicsTextItem();
        int x = tile.value()->point.x();
        int y = tile.value()->point.y();

        text->setPlainText(QString("%1,%2").arg(x).arg(y));
        text->setPos(x_scene(x),y_scene(y));
        text->adjustSize();
        scene->addItem(text);

    }

}

void Game::printAllTiles()
{
    QMapIterator<int,Tile*> tile(tiles);
    while (tile.hasNext()){
        tile.next();
    }
}

void Game::drawOpenRect(int x, int y)
{
    QGraphicsRectItem *rect = new QGraphicsRectItem(x_scene(x)+4,y_scene(y)+4,map_tile_size-4,map_tile_size-4);
    rect->setBrush(QBrush(Qt::yellow));
    scene->addItem(rect);

}

void Game::drawClosedRect(int x, int y)
{
    QGraphicsRectItem *rect = new QGraphicsRectItem(x_scene(x)+4,y_scene(y)+4,map_tile_size-4,map_tile_size-4);
    rect->setBrush(QBrush(Qt::red));
    rect->setZValue(1);
    scene->addItem(rect);
}
