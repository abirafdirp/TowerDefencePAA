#include "Game.h"
#include "Tower.h"
#include "MyApplication.h"
#include "EnemyBlueSlime.h"
#include "Wall.h"
#include "BuildWall.h"
#include "Tile.h"
#include "Path.h"
#include "bullet.h"
#include <QGraphicsScene>
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
#include <qmath.h>
#include <QCursor>
#include <QMessageBox>

Game::Game()
{
    setMouseTracking(true);
    setMapTile(20,10,64); // but start from 0
    createScene();

    cursor = new QPixmap(":/util/assets/tank/crosshair_blue_large.png");
    //cursor->setOffset(-25,-25);
    //cursor->setZValue(999);
    //QApplication::setOverrideCursor(Qt::BlankCursor);

    QCursor(cursor);

    createMapTiles(":/floor/assets/floor/dirt.png");
    //drawTilesOverlay(":/util/assets/util/sTrackBorder_0.png");
    //drawTilesPoint();
    //printAllTiles();

    spawn1 = tiles.value(indexOfPoint(0,5));
    spawn1->setPos(x_scene(0),y_scene(5));
    dest1 = tiles.value(indexOfPoint(19,5));
    dest1->setPos(x_scene(19),y_scene(5));

    QGraphicsPixmapItem *keybind = new QGraphicsPixmapItem(QPixmap(":/menu/assets/menu/menu.png"));
    scene->addItem(keybind);
    keybind->setScale(0.6);
    keybind->setOffset(400,430);
    keybind->setZValue(99999);

    QGraphicsPixmapItem *start = new QGraphicsPixmapItem(QPixmap(":/floor/assets/floor/start.png"));
    start->setPos(x_scene(0),y_scene(5));
    start->setScale(0.5);
    scene->addItem(start);

    QGraphicsPixmapItem *finish = new QGraphicsPixmapItem(QPixmap(":/floor/assets/floor/finish.png"));
    finish->setPos(x_scene(19),y_scene(5));
    finish->setScale(0.5);
    scene->addItem(finish);

    int index = indexOfPoint(19,4);
    tower = new Tower(*this,this->tiles.value(index)->x(),this->tiles.value(index)->y());
    tiles.value(indexOfPoint(19,4))->walkable = false;
    base_reload_bar = new QGraphicsRectItem(0,0,map_tile_size-13,10);
    base_reload_bar->setBrush(QBrush(Qt::red));
    base_reload_bar->setZValue(1);
    base_reload_bar->setPos(x_scene(19)+4,y_scene(4)-15);
    scene->addItem(base_reload_bar);

    reload_bar_placeholder = new QGraphicsRectItem(x_scene(19)+4,y_scene(4)-15,51,10);
    reload_bar_placeholder->setBrush(QBrush(Qt::green));
    reload_bar_placeholder->setZValue(999);
    scene->addItem(reload_bar_placeholder);

    buildwall = new BuildWall(*this);

    score_text = new QGraphicsTextItem(QString("Skor : %1").arg(score));
    score_text->setPos(1190,10);
    score_text->setScale(1.5);
    scene->addItem(score_text);
}

void Game::generatePath() {
    path = new Path(*this,*spawn1,*dest1);

    if (path->destfound){
        buildwall->setZValue(-9999);
        spawner_timer = new QTimer();
        connect(spawner_timer,SIGNAL(timeout()),this,SLOT(spawnBlueSlime()));
        spawner_timer->start(5000);
        spawnBlueSlime();
    }
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

void Game::spawnBlueSlime()
{
    increase_spawner++;
    BlueSlime * blueslime = new BlueSlime(*this, *path);
    if (increase_spawner % 4== 0){
        if (spawner_timer->interval() > 2000){
            spawner_timer->setInterval(spawner_timer->interval() - 500);
        }
    }
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

void Game::restartScene()
{
    Game *game = new Game();
    game->show();
    delete this;
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
    if (cursor !=nullptr){
        //cursor->setPos(event->pos());
    }

    QLineF ln(QPointF(tower->x() + 5,tower->y() + 40),QPointF(event->pos()));
    double angle =  ((-1 * ln.angle()) + 90);
    tower->setRotation(angle);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton){

       if (can_fire == true){
           can_fire = false;

           if (reload_bar_placeholder != nullptr){
               scene->removeItem(reload_bar_placeholder);
               reload_bar_placeholder = nullptr;
           }

           if (redraw_reload_bar == true){
               delete reload_bar;
               redraw_reload_bar = false;
           }

           // bullet
           Bullet *bullet = new Bullet(*this);
           QLineF ln(QPointF(tower->x() + 5,tower->y() + 40),QPointF(event->pos()));
           bullet->setOffset(35,-10);
           bullet->setPos(ln.x1(), ln.y1());
           double angle =  ((-1 * ln.angle()));
//           QPointF *target = new QPointF(100,100);
//           bullet->setTarget(target);
           bullet->setRotation(angle);
           bullet->setTarget(event->pos());
           scene->addItem(bullet);

           reload_bar = new QGraphicsRectItem(x_scene(19)+4,y_scene(4)-15,51,10);
           reload_bar->setBrush(QBrush(Qt::green));
           reload_bar->setZValue(999);
           scene->addItem(reload_bar);

           smoke_timer = new QTimer();
           reload_timer = new QTimer();
           reload_bar_timer = new QTimer();
           connect(smoke_timer,SIGNAL(timeout()),this,SLOT(animateSmoke()));
           connect(reload_timer,SIGNAL(timeout()),this,SLOT(reloadTimer()));
           connect(reload_bar_timer,SIGNAL(timeout()),this,SLOT(reloadBarTimer()));
           smoke_timer->start(50);
           reload_timer->start(3000);
           reload_bar_timer->start(100);

           // smoke on barrel
           smoke = new QGraphicsPixmapItem(QPixmap(":/tank/assets/tank/smokeGrey4.png"));
           smoke->setOffset(-25,-50);
           smoke->setPos(ln.x1(), ln.y1());
           smoke->setRotation(angle);
           smoke->setZValue(199);
           scene->addItem(smoke);
       }


    }
}

//void Game::keyPressEvent(QKeyEvent *ev)
//{
//    switch (ev->key())
//    {
//        case Qt::Key_Return:
//            buildwall = new BuildWall(*this);
//            scene->setFocusItem(buildwall);
//            break;
//    }
//}



void Game::animateSmoke()
{
    if (smoke->opacity() > 0) {
        smoke->setOpacity(smoke->opacity() - 0.05);
    }
    else {
        disconnect(smoke_timer,SIGNAL(timeout()),this,SLOT(animateSmoke()));
        delete smoke;
    }
}

void Game::reloadTimer()
{
    can_fire = true;
    disconnect(reload_timer,SIGNAL(timeout()),this,SLOT(reloadTimer()));
}

void Game::reloadBarTimer()
{
    if (reload_bar_threshold <= 2600) {
        reload_bar_threshold += 100;
        reload_bar->setRect(base_reload_bar->pos().x(),base_reload_bar->pos().y(),reload_bar_length,10);
        reload_bar_length+=2;
    }
    else {
        reload_bar_threshold = 0;
        disconnect(reload_bar_timer,SIGNAL(timeout()),this,SLOT(reloadBarTimer()));
        redraw_reload_bar = true;
        reload_bar_length = 0;
    }
}


