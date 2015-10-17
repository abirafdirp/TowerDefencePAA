#include "MyApplication.h"
#include "Game.h"
#include <QTime>
#include <QObject>

MyApplication::MyApplication(int argc, char *argv[]):QApplication(argc,argv)
{
    Game *game = new Game();
    game->show();
    game->generatePath();
}

void MyApplication::delay(int msecs)
{
    QTime dieTime= QTime::currentTime().addMSecs(msecs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
