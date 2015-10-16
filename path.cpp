#include "Path.h"
#include "Game.h"
#include <QDebug>

Path::Path(Game &game_, Tile &spawn_, Tile &dest_) : game(game_), spawn(spawn_), dest(dest_)
{
    QList<Tile*> tiles = game.getTiles();
    spawn.g = 0;
    spawn.h = 0;
    open.insert(spawn.getF(),&spawn);
    while (!open.empty()){
        current = open.first();
        closed.append(current);
        // generate adjacent tiles
        for(int adjacentX=-1;adjacentX <=1;adjacentX++){
            for(int adjacentY=-1;adjacentY <=1;adjacentY++){
                adjacent.append();
            }
        }


    }
}
