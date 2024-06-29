#ifndef REALTIMECLASS_H
#define REALTIMECLASS_H
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>

class rtTextItem: public QGraphicsTextItem
{
public:
    rtTextItem(QString qs);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneMouseEvent* event);
    void hoverLeaveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // REALTIMECLASS_H
