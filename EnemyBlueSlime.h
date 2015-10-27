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
    void startSpawner();
private:
    Game &game;
    int animation_index = 0;
    Path &path;
    int lenindex;

    QTimer *spawner_timer;

public slots:
    void spawner();
    void move();
};


#endif // ENEMYBLUESLIME

