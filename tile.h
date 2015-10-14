#ifndef PATHTILE
#define PATHTILE
#include <QString>
#include <QGraphicsPixmapItem>
#include <QObject>
#include "Game.h"

class Tile: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tile(QGraphicsItem * parent=0);
    QPoint point;
    QPoint point_real;

    void setPoint(QPoint point);
    void setPointReal(QPoint point);

};

#endif // PATHTILE

