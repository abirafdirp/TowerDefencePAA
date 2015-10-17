#ifndef BUILDWALLICON_H
#define BUILDWALLICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>


class BuildWallIcon: public QGraphicsPixmapItem{
public:
    BuildWallIcon(QGraphicsItem * parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // BUILDWALLICON_H
