#include "Path.h"
#include "Game.h"
#include "MyApplication.h"
#include <QDebug>
#include <QMapIterator>

Path::Path(Game &game_, Tile &spawn_, Tile &dest_) : game(game_), spawn(spawn_), dest(dest_)
{
    int indexdebug = 0;

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
        game.drawClosedRect(current_x_point,current_y_point);

        // generate adjacent tiles and process it
        for(int adjacentXOffset=-1;adjacentXOffset <=1;adjacentXOffset++){
            for(int adjacentYOffset=-1;adjacentYOffset <=1;adjacentYOffset++){

                // make a reference to that tile
                int adjacentPointX = current->point.x() + adjacentXOffset;
                int adjacentPointY = current->point.y() + adjacentYOffset;
                Tile *adjacent_tile = tiles.value(game.indexOfPoint(adjacentPointX,adjacentPointY));

                // if the adjacent tile is not walkable or is in closed map then ignore it
                if ( (!adjacent_tile->walkable) || (closedContains(*adjacent_tile)) ) {
                    continue;
                }


                // if the adjacent tile is not in open map
                if ( (adjacent_tile->g < current->g) || (!openContains(*adjacent_tile))){
                    adjacent_tile->parent_tile = current;

                    // determine the G
                    if ((adjacentXOffset == adjacentYOffset) || (adjacentXOffset + adjacentYOffset == 0)){
                        adjacent_tile->g = current->g + 14;
                    }
                    else {
                        adjacent_tile->g = current->g + 10;
                    }

                    // determine the H using manhattan
                    int manhattan = 10 * (abs(dest.point.x() - adjacent_tile->point.x()) + abs(dest.point.y() - adjacent_tile->point.y()));
                    adjacent_tile->h = manhattan;

                    // determine F
                    adjacent_tile->f = adjacent_tile->processF();

                    // add to open  after processing F
                    open.insertMulti(adjacent_tile->f,adjacent_tile);
                    drawTileDebug(*adjacent_tile);

                    // DEBUG
                    game.drawOpenRect(adjacentPointX,adjacentPointY);
                }


            } //endfor
        } //endfor
        qDebug() << indexdebug;
        indexdebug++;
        printOpen();
        MyApplication::delay(500);
    } // end while
}

void Path::drawTileDebug(Tile &tile)
{
    QGraphicsTextItem *text = new QGraphicsTextItem();
    int x = tile.point.x();
    int y = tile.point.y();
    int f = tile.f;
    int g = tile.g;
    int h = tile.h;

    text->setPlainText(QString("F : %1 \nG : %2 \nH : %3").arg(f).arg(g).arg(h));
    text->setPos(game.x_scene(x),game.y_scene(y));
    text->adjustSize();
    text->setZValue(100);
    game.scene->addItem(text);

}

void Path::updateTileDebug(Tile &tile)
{

    QGraphicsTextItem *text = new QGraphicsTextItem();
    int x = tile.point.x();
    int y = tile.point.y();
    int f = tile.f;
    int g = tile.g;
    int h = tile.h;

    text->setPlainText(QString("F : %1 \nG : %2 \nH : %3").arg(f).arg(g).arg(h));
    text->setPos(game.x_scene(x),game.y_scene(y));
    text->adjustSize();
    text->setZValue(102);
    game.scene->addItem(text);

    QGraphicsRectItem *rect = new QGraphicsRectItem(game.x_scene(x)+4,game.y_scene(y)+4,game.map_tile_size-4,game.map_tile_size-4);
    rect->setBrush(QBrush(Qt::yellow));
    rect->setZValue(101);
    game.scene->addItem(rect);
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


