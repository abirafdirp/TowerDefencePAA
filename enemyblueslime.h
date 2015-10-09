#ifndef ENEMYBLUESLIME
#define ENEMYBLUESLIME
#include <QGraphicsPixmapItem>
#include <QObject>

class BlueSlime: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BlueSlime(QGraphicsItem * parent=0);
public slots:
    void move();
};


#endif // ENEMYBLUESLIME

