#ifndef ENEMYBLUESLIME
#define ENEMYBLUESLIME

#include "Enemy.h"
#include <QGraphicsPixmapItem>
#include <QObject>

class Path;

class BlueSlime: public Enemy{
    Q_OBJECT
public:
    BlueSlime(Path &path_, QGraphicsItem * parent=0);
    Path &path;
private:
    int lenindex;
public slots:
    void move();
};


#endif // ENEMYBLUESLIME

