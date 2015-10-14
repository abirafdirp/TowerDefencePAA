#include "Game.h"
#include "Tower.h"
#include "EnemyBlueSlime.h"
#include "Wall.h"
#include "Tile.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QPoint>

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
    QPoint spawn1 = QPoint(4,5);
    QPoint dest1 = QPoint(1,8);
    spawnBlueSlime(spawn1);
}

void Game::createMapTiles(QString filename)
{
    QList<Tile*> tiles[map_tiles_x][map_tiles_y];
    for(int i = 0; i < map_tiles_x; i++){
        for(int n = 0; n < map_tiles_y; n++){

            // set the floor sprite
            Tile * tile = new Tile();
            tile->setPixmap(QPixmap(filename));
            tile->setScale(0.5);
            tile->setZValue(0);
            tile->setPos(i*64,n*64);
            tile->setPoint(QPoint(i,n));
            tile->setPointReal(QPoint(this->map_tile_size*i,this->map_tile_size*n));

            tiles[i][n].append(tile);
            scene->addItem(tile);
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

void Game::generatePath(QPoint spawn, QPoint dest)
{
    for(int i = 0; i < map_tiles_x; i++){
        for(int n = 0; n < map_tiles_y; n++){

            // set the floor overlay
            AStarTile tile;
            tile.x = i;
            tile.y = n;
            tile.walkable = true;
        }
    }
}

Game &Game::getInstance()
{
    static Game instance;
    return instance;
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

void Game::spawnBlueSlime(QPoint point)
{
    BlueSlime * blueslime = new BlueSlime();
    scene->addItem(blueslime);
    blueslime->setPos(x_scene(point.x()),y_scene(point.y()));
    QTimer * fps = new QTimer(this);
    connect(fps,SIGNAL(timeout()),blueslime,SLOT(move()));
    fps->start(1000);
}

int Game::getTileSize()
{
    return this->map_tile_size;
}

int Game::x_scene(int x)
{
    return x * this->map_tile_size;
}

int Game::y_scene(int y)
{
    return y * this->map_tile_size;
}

void Game::test()
{
    qDebug() << "fuck2";
}

