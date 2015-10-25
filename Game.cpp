#include "Game.h"
#include "Tower.h"
#include "EnemyBlueSlime.h"
#include "Wall.h"
#include "BuildWall.h"
#include "Tile.h"
#include "Path.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QPoint>
#include <QMap>
#include <QMapIterator>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QLineF>
#include <QPointF>

Game::Game()
{
    setMouseTracking(true);
    setMapTile(20,10,64); // but start from 0
    createScene();
    createMapTiles(":/floor/assets/floor/dirt.png");
    //drawTilesOverlay(":/util/assets/util/sTrackBorder_0.png");
    //drawTilesPoint();
    //printAllTiles();

    QGraphicsRectItem *rect = new QGraphicsRectItem(x_scene(1)+4,y_scene(5)+4,map_tile_size-4,map_tile_size-4);
    rect->setBrush(QBrush(Qt::gray));
    rect->setZValue(100000);
    scene->addItem(rect);

    QGraphicsRectItem *rect2 = new QGraphicsRectItem(x_scene(19)+4,y_scene(5)+4,map_tile_size-4,map_tile_size-4);
    rect2->setBrush(QBrush(Qt::gray));
    rect2->setZValue(100000);
    scene->addItem(rect2);

    int index = indexOfPoint(19,4);
    Tower *tower = new Tower(*this,this->tiles.value(index)->x(),this->tiles.value(index)->y());

    BuildWall *wall = new BuildWall(*this);
}

void Game::generatePath() {
    Tile *spawn1 = tiles.value(indexOfPoint(1,5));
    Tile *dest1 = tiles.value(indexOfPoint(19,5));
    Path *path = new Path(*this,*spawn1,*dest1);
    spawnBlueSlime(*spawn1,*dest1, *path);
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
            tile->parent_tile = nullptr;

            /* randomize wall
            if ((y == 4) || (y == 5) || (y == 6) || (y == 7) || (y == 3)){
                tile->setPixmap(QPixmap(":/wall/assets/wall/brick_red.png"));
                tile->walkable = false;
            }
            if (x % 2 == 1){
                tile->setPixmap(QPixmap(filename));
                tile->walkable = true;
            }*/


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

void Game::setMapTile(int map_tiles_x, int map_tiles_y, int map_tile_size_)
{
    map_width_in_tiles = map_tiles_x;
    map_height_in_tiles = map_tiles_y;
    map_tile_size = map_tile_size_;
}

void Game::spawnBlueSlime(Tile &spawn, Tile &dest, Path &path)
{
    BlueSlime * blueslime = new BlueSlime(path);
    scene->addItem(blueslime);
    blueslime->setPos(x_scene(spawn.point.x()),y_scene(spawn.point.y()));
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

void Game::drawTilesPoint()
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

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton){
       qDebug() << "yes";
    }
    QLineF ln(QPointF(0,0),QPointF(100,100));
    int angle = -1 * ln.angle();
    this->tower->setRotation(angle);
}
