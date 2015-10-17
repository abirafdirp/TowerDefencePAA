#ifndef ENEMYBLUESLIME
#define ENEMYBLUESLIME

#include "Enemy.h"
#include <QGraphicsPixmapItem>
#include <QObject>

class BlueSlime: public Enemy{
    Q_OBJECT
public:
    BlueSlime(QGraphicsItem * parent=0);
public slots:
    void move();
};


#endif // ENEMYBLUESLIME

