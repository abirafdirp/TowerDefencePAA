#ifndef ENEMYBLUESLIME
#define ENEMYBLUESLIME

#include "Enemy.h"
#include <QGraphicsPixmapItem>
#include <QObject>

class Path;
class Game;

class BlueSlime: public Enemy{
    Q_OBJECT
public:
    BlueSlime(Game &game_, Path &path_, QGraphicsItem * parent=0);
private:
    Game &game;
    int animation_index = 0;
    Path &path;
    int lenindex;
public slots:
    void move();
};


#endif // ENEMYBLUESLIME

