#ifndef ITEM_H
#define ITEM_H
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QtSvgWidgets/QGraphicsSvgItem>
extern const int itemType;
extern const int itemName;
extern const int itemHighlight;

class stationItem : public QGraphicsEllipseItem //普通站继承自QGraphics椭圆
{
public:
    static const int myType = 1;//用于设置该item的itemType
    stationItem(int x, int y);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

class transferItem : public QGraphicsSvgItem    //换乘站导入SVG图标
{
public:
    static const int myType = 1;
    transferItem(int x, int y);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

extern QGraphicsItemGroup* stationGroup;
extern QGraphicsItemGroup* highlightGroup;

#endif // ITEM_H
