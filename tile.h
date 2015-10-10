#ifndef PATHTILE
#define PATHTILE
#include <QString>
#include <QGraphicsPixmapItem>
#include <QObject>

class Tile: public QObject, public QGraphicsPixmapItem {
public:
    Tile();
    int x;
    int y;

    int x_real;
    int y_real;

    void setX(int x);
    void setY(int y);
    void setXReal(int x);
    void setYReal(int y);

};

#endif // PATHTILE

