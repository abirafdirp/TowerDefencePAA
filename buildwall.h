#ifndef BUILDWALL
#define BUILDWALL

#endif // BUILDWALL

#include <QGraphicsPixmapItem>

class Game;

class BuildWall: public QGraphicsPixmapItem{
public:
    BuildWall(Game &game_);
    Game &game;

private:

    bool onBorder = true;
    void keyPressEvent(QKeyEvent *ev);


};
