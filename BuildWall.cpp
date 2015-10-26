#include "BuildWall.h"
#include "Game.h"
#include "MyApplication.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include "Path.h"


BuildWall::BuildWall(Game &game_) : game(game_)
{
    setPixmap(QPixmap(":/wall/assets/wall/brick_red.png"));
    setScale(0.5);
    game.scene->addItem(this);
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setFocus();
}

void BuildWall::keyPressEvent(QKeyEvent *ev)
{
    int grid = game.map_tile_size;
    switch (ev->key())
    {
        case Qt::Key_Down:
            if (y() < grid * (game.map_height_in_tiles - 1)){
               setPos(x(),y() + grid);
            }
            break;
        case Qt::Key_Up:
            if (y() != 0){
                setPos(x(),y() - grid);
            }
            break;
        case Qt::Key_Right:
            if (x() < grid * (game.map_width_in_tiles - 1)){
                setPos(x() + grid,y());
            }
            break;
        case Qt::Key_Left:
            if (x() != 0){
               setPos(x() - grid,y());
            }
            break;
        case Qt::Key_Space:{
            qDebug() << x() << game.spawn1->x() << y() << game.spawn1->y();

            if (((x() == game.spawn1->x()) && (y() == game.spawn1->y())) || ((y() == game.dest1->y()) && (x() == game.dest1->x()))){
            }
            else if((x() == game.dest1->x()) && (y() == game.dest1->y() - 64)){

            }
            else {
                int buildwall_x = x() / game.map_tile_size;
                int buildwall_y = y() / game.map_tile_size;
                Tile *tile = game.tiles.value(game.indexOfPoint(buildwall_x,buildwall_y));
                tile->walkable = false;
                tile->setPixmap(QPixmap(":/wall/assets/wall/brick_red.png"));
            }
            break;

        }
        case Qt::Key_Return:
            game.generatePath();
            break;
    }
}
