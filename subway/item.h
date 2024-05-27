#ifndef STATIONITEM_H
#define STATIONITEM_H
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QtSvgWidgets/QGraphicsSvgItem>

class stationItem : public QGraphicsEllipseItem //普通站继承自QGraphics椭圆
{
public:
    stationItem(int x, int y);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

class transferItem : public QGraphicsSvgItem    //换乘站导入SVG图标
{
public:
    transferItem(int x, int y);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};
#endif // STATIONITEM_H
