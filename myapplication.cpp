#include "MyApplication.h"
#include "Game.h"
#include <QObject>

MyApplication::MyApplication(int argc, char *argv[]):QApplication(argc,argv)
{
    Game& game = Game::getInstance();
    game.show();
}
