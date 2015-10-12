#ifndef PATHTILE
#define PATHTILE
#include <QString>
#include <QGraphicsPixmapItem>
#include <QObject>

class Tile: public QObject, public QGraphicsPixmapItem {
public:
    Tile(QGraphicsItem * parent=0);
    QPoint point;
    QPoint point_real;

    void setPoint(QPoint point);
    void setPointReal(QPoint point);

};

#endif // PATHTILE

