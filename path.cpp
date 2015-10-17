#include "Path.h"
#include "Game.h"
#include "MyApplication.h"
#include <QDebug>
#include <QMapIterator>

Path::Path(Game &game_, Tile &spawn_, Tile &dest_) : game(game_), spawn(spawn_), dest(dest_)
{
    int indexdebug;

    QMap<int,Tile*> tiles = game.getTiles();

    // add spawn tiles to open map. Initialize its f with 0 (actually it doesn't matter because it is the only one in open map)
    spawn.g = 0;
    spawn.h = 0;
    spawn.f = spawn.processF();
    open.insert(spawn.f,&spawn);

    while (!open.empty()){

        // look for the lowest F, because QMap is sorted we take the first tile
        current = open.first();
        // qDebug() << current->point.x() << " " << current->point.y();

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
        closed.insert(current->f,current);
        game.drawClosedRect(current_x_point,current_y_point);

        // generate adjacent tiles and process it
        for(int adjacentX=-1;adjacentX <=1;adjacentX++){
            for(int adjacentY=-1;adjacentY <=1;adjacentY++){

                // ignore the current tile
                if ((adjacentX == 0) && (adjacentY == 0)){
                    continue;
                }

                // make a reference to that tile
                int x = current->point.x() + adjacentX;
                int y = current->point.y() + adjacentY;
                Tile *adjacent_tile = tiles.value(game.indexOfPoint(x,y));
                game.drawOpenRect(x,y);

                // if the adjacent tile is not walkable or is in closed map then ignore it
                if ( (!adjacent_tile->walkable) || (closed.contains(game.indexOfPoint(x,y))) ) {
                    continue;
                }

                // if the adjacent tile is not in open map
                if (!open.contains(game.indexOfPoint(x,y))){
                    qDebug() << openContains(*adjacent_tile) << indexdebug;

                    //qDebug() << adjacent_tile->point.x() << " " << adjacent_tile->point.y() << indexdebug;
                    adjacent_tile->parent_tile = current;

                    // determine the G
                    if ((adjacentX == adjacentY) || (adjacentX + adjacentY == 0)){
                        adjacent_tile->g = 14;
                    }
                    else {
                        adjacent_tile->g = 10;
                    }

                    // determine the H using manhattan
                    int manhattan = 10 * (abs(dest.point.x() - adjacent_tile->point.x()) + abs(dest.point.y() - adjacent_tile->point.y()));
                    adjacent_tile->h = manhattan;

                    // determine F
                    adjacent_tile->f = adjacent_tile->processF();

                    // add to closed after processing F
                    open.insert(adjacent_tile->f,adjacent_tile);
                    qDebug() << indexdebug;
                    drawTileDebug(*adjacent_tile);
                }

                else {

                }




            } //endfor
        } //endfor

        MyApplication::delay(500);
        indexdebug++;



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

    text->setPlainText(QString("F : %1 \n G : %2 \n H : %3").arg(f).arg(g).arg(h));
    text->setPos(game.x_scene(x),game.y_scene(y));
    text->adjustSize();
    game.scene->addItem(text);

}

bool Path::openContains(Tile &tile)
{
    Tile *tile_to_be_checked = &tile;
    QMapIterator<int,Tile*> open_tile(open);
    while (open_tile.hasNext()){
        open_tile.next();

    }
}


