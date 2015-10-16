#include "Path.h"
#include "Game.h"
#include "MyApplication.h"
#include <QDebug>

Path::Path(Game &game_, Tile &spawn_, Tile &dest_) : game(game_), spawn(spawn_), dest(dest_)
{
    int indexdebug;

    QMap<int,Tile*> tiles = game.getTiles();
    spawn.g = 0;
    spawn.h = 0;
    spawn.f = spawn.processF();
    open.insert(spawn.f,&spawn);
    while (!open.empty()){
        current = open.first();
        qDebug() << current->point.x() << " " << current->point.y();

        int current_x_point = current->point.x() ;
        int current_y_point = current->point.y() ;
        int dest_x_point = dest.point.x();
        int dest_y_point = dest.point.y();
        if ((current_x_point == dest_x_point) && (current_y_point == dest_y_point)) {
            break;
        }

        open.take(open.firstKey());
        closed.insert(current->f,current);
        game.drawClosedRect(current_x_point,current_y_point);

        // generate adjacent tiles

        for(int adjacentX=-1;adjacentX <=1;adjacentX++){
            for(int adjacentY=-1;adjacentY <=1;adjacentY++){

                // ignore the current tile
                if ((adjacentX == 0) && (adjacentY == 0)){
                    continue;
                }

                int x = current->point.x() + adjacentX;
                int y = current->point.y() + adjacentY;
                Tile *adjacent_tile = tiles.value(game.indexOfPoint(x,y));
                game.drawOpenRect(x,y);

                if ( (!adjacent_tile->walkable) || (closed.contains(game.indexOfPoint(x,y))) ) {
                    continue;
                }

                if (!open.contains(game.indexOfPoint(x,y))){

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
                }

                else {

                }




            } //endfor
        } //endfor

        MyApplication::delay(500);
        indexdebug++;



    } // end while
}

int Path::generateG(Tile &tile)
{

}

int Path::generateH(Tile &tile)
{

}


