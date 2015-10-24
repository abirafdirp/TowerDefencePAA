#include "Path.h"
#include "Game.h"
#include "MyApplication.h"
#include <QDebug>
#include <QMapIterator>
#include <QListIterator>

Path::Path(Game &game_, Tile &spawn_, Tile &dest_) : game(game_), spawn(spawn_), dest(dest_)
{
    //int indexdebug = 0;

    QMap<int,Tile*> tiles = game.getTiles();

    // add spawn tiles to open map. Initialize its f with 0.
    spawn.g = 0;
    spawn.h = 0;
    spawn.f = spawn.processF();
    open.insertMulti(spawn.f,&spawn);

    while (!open.empty()){

        // look for the lowest F, because QMap is sorted we take the first tile
        current = open.first();

        int current_x_point = current->point.x() ;
        int current_y_point = current->point.y() ;
        int dest_x_point = dest.point.x();
        int dest_y_point = dest.point.y();

        // break out of loop if current is dest
        if ((current_x_point == dest_x_point) && (current_y_point == dest_y_point)) {
            break;
        }

        // switch it to closed map
        open.take(open.firstKey());
        closed.insertMulti(game.indexOfPoint(current->point.x(),current->point.y()),current);
        //drawClosedRect(current_x_point,current_y_point);
        //drawTileDebug(*current);

        // generate adjacent tiles and process it
        for(int adjacentXOffset=-1;adjacentXOffset <=1;adjacentXOffset++){
            for(int adjacentYOffset=-1;adjacentYOffset <=1;adjacentYOffset++){

                /* validate the adjacent point, if it goes out of the map then ignore it,
                 * if not make a reference to that tile */
                int adjacentPointX = current->point.x() + adjacentXOffset;
                int adjacentPointY = current->point.y() + adjacentYOffset;
                if ((adjacentPointX >= game.map_width_in_tiles) || (adjacentPointY >= game.map_height_in_tiles) || (adjacentPointX < 0) || (adjacentPointY < 0)){
                    continue;
                }
                Tile *adjacent_tile = tiles.value(game.indexOfPoint(adjacentPointX,adjacentPointY));

                // if the adjacent tile is not walkable or is in closed map then ignore it
                if ( (!adjacent_tile->walkable) || (closedContains(*adjacent_tile)) ) {
                    continue;
                }

                // re-calculate g of all adjacent tiles to later check if it's better or not to get there directly
                int new_g;
                if ((adjacentXOffset == adjacentYOffset) || (adjacentXOffset + adjacentYOffset == 0)){
                    new_g = current->g + 14;
                }
                else {
                    new_g = current->g + 10;
                }


                // if the adjacent tile is not in open map
                if ((!openContains(*adjacent_tile)) || new_g < adjacent_tile->g){
                    adjacent_tile->parent_tile = current;
                    //drawTileParent(*adjacent_tile,*current);

                    adjacent_tile->g = new_g;

                    // determine the H using manhattan
                    int manhattan = 10 * (abs(dest.point.x() - adjacent_tile->point.x()) + abs(dest.point.y() - adjacent_tile->point.y()));
                    adjacent_tile->h = manhattan;

                    // determine F
                    adjacent_tile->f = adjacent_tile->processF();

                    // add to open after processing F
                    open.insertMulti(adjacent_tile->f,adjacent_tile);
                    //drawTileFGH(*adjacent_tile);

                    // DEBUG
                    //drawOpenRect(adjacentPointX,adjacentPointY);
                    //drawTileDebug(*adjacent_tile);
                }

            } //endfor
        } //endfor
        update_z_index++;
        //qDebug() << indexdebug;
        //indexdebug++;
        //printOpen();
        MyApplication::delay(20);
    } // end while
    reconstructPath();
    //printPath();
}
bool Path::openContains(Tile &tile)
{
    Tile *tile_to_be_checked = &tile;
    QMapIterator<int,Tile*> open_tile(open);
    while (open_tile.hasNext()){
        open_tile.next();
        if ((tile_to_be_checked->point.x() == open_tile.value()->point.x()) && (tile_to_be_checked->point.y() == open_tile.value()->point.y())){
            return true;
        }

    }
    return false;
}

bool Path::closedContains(Tile &tile)
{
    Tile *tile_to_be_checked = &tile;
    QMapIterator<int,Tile*> closed_tile(closed);
    while (closed_tile.hasNext()){
        closed_tile.next();
        if ((tile_to_be_checked->point.x() == closed_tile.value()->point.x()) && (tile_to_be_checked->point.y() == closed_tile.value()->point.y())){
            return true;
        }

    }
    return false;
}

void Path::printOpen()
{
    QMapIterator<int,Tile*> tile(open);
    qDebug() << "START";
    while(tile.hasNext()){
        tile.next();
        qDebug() << "(" << tile.value()->point.x() << "," << tile.value()->point.y() << ")";
    }
    qDebug() << "END";
}

void Path::reconstructPath()
{
    Tile *current = &dest;
    while (1){
        path.append(current);
        current = current->parent_tile;
        if ((current->point.x() == spawn.point.x()) && (current->point.y() == spawn.point.y())){
            break;
        }
    }
}

void Path::drawTileDebug(Tile &tile)
{
    update_z_index+=1;
    int x = tile.point.x();
    int y = tile.point.y();

    if (!closedContains(tile)){
        QGraphicsRectItem *rect = new QGraphicsRectItem(game.x_scene(x)+4,game.y_scene(y)+4,game.map_tile_size-4,game.map_tile_size-4);
        rect->setBrush(QBrush(Qt::yellow));
        rect->setZValue(update_z_index);
        game.scene->addItem(rect);
    }

    else {
        QGraphicsRectItem *rect = new QGraphicsRectItem(game.x_scene(x)+4,game.y_scene(y)+4,game.map_tile_size-4,game.map_tile_size-4);
        rect->setBrush(QBrush(Qt::red));
        rect->setZValue(update_z_index);
        game.scene->addItem(rect);
    }

    if (tile.parent_tile != nullptr){
        Tile *parent = tile.parent_tile;
        QGraphicsPixmapItem *arrow = new QGraphicsPixmapItem(QPixmap(":/util/assets/util/arrowUp.png"));
        arrow->setScale(0.35);
        arrow->setZValue(update_z_index+10);
        arrow->setTransformOriginPoint(arrow->boundingRect().center());

        int tile_point_x = tile.point.x();
        int tile_point_y = tile.point.y();
        int tile_center_x = (game.x_scene(tile_point_x));
        int tile_center_y = (game.y_scene(tile_point_y));
        QPoint tile_center = QPoint(tile_center_x,tile_center_y);

        arrow->setPos(tile_center);
        if (parent->point.x() > tile.point.x()){
            if (parent->point.y() > tile.point.y()){
                arrow->setRotation(135);
            }
            else if(parent->point.y() < tile.point.y()){
                arrow->setRotation(45);
            }
            else {
               arrow->setRotation(90);
            }
        }
        else if (parent->point.x() < tile.point.x()){
            if (parent->point.y() > tile.point.y()){
                arrow->setRotation(-135);
            }
            else if(parent->point.y() < tile.point.y()){
                arrow->setRotation(-45);
            }
            else {
               arrow->setRotation(-90);
            }
        }
        else if ((parent->point.x() == tile.point.x()) && (parent->point.y() > tile.point.y())){
            arrow->setRotation(180);
        }

        game.scene->addItem(arrow);
    }

    QGraphicsTextItem *text = new QGraphicsTextItem();
    x = tile.point.x();
    y = tile.point.y();
    int f = tile.f;
    int g = tile.g;
    int h = tile.h;

    text->setPlainText(QString("F : %1 \nG : %2 \nH : %3").arg(f).arg(g).arg(h));
    text->setPos(game.x_scene(x),game.y_scene(y));
    text->adjustSize();
    text->setZValue(update_z_index+10);
    game.scene->addItem(text);

}

void Path::printPath()
{
    foreach (Tile *tile, path) {
        int x = tile->point.x();
        int y = tile->point.y();
        QGraphicsRectItem *rect = new QGraphicsRectItem(game.x_scene(x)+20,game.y_scene(y)+20,game.map_tile_size-20,game.map_tile_size-20);
        rect->setBrush(QBrush(Qt::green));
        rect->setZValue(10000);
        game.scene->addItem(rect);
    }
}

