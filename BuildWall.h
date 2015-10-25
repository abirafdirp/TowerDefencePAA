#ifndef BUILDWALL
#define BUILDWALL

#endif // BUILDWALL

#include <QGraphicsPixmapItem>
#include <QObject>

class Game;

class BuildWall: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BuildWall(Game &game_);
    Game &game;

private:
    void keyPressEvent(QKeyEvent *ev);

};
