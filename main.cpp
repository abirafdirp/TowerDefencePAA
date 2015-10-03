#include "mainwindow.h"
#include <QApplication>
#include "game.h"

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game * game = new Game();
    game->setMapTile(15,10,64);
    game->createScene();
    game->createMapTiles(":/floor/assets/floor/dirt.png");
    game->createTilesOverlay(":/util/assets/util/sTrackBorder_0.png");
    game->setCursor(":/wall/assets/wall/brick_red.png");
    game->show();

    return a.exec();
}
