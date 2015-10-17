#ifndef TOWER
#define TOWER

#include <QGraphicsPixmapItem>

class Tower: public QGraphicsPixmapItem {
   public:
    Tower(QGraphicsItem * parent=0);
   private:
    QGraphicsPolygonItem * attack_area;

};

#endif // TOWER

