#include "Path.h"
#include "Game.h"
#include <QDebug>

Path::Path(Game &game_, Tile &spawn_, Tile &dest_) : game(game_), spawn(spawn_), dest(dest_)
{
    QList<Tile*> tiles = game.getTiles();
    open.append(&spawn);
    open.first()->force = 0;
    open.first()->heuristic = 0;
    /*while (!open.empty()){

        // generate adjacent tiles
        for(int adjacentX=-1;adjacentX <=1;adjacentX++){
            for(int adjacentY=-1;adjacentY <=1;adjacentY++){
                open.append(tiles.at());
            }
        }

        current = open
    }*/
}
