#ifndef ITEM_H
#define ITEM_H
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QtSvgWidgets/QGraphicsSvgItem>
extern const int itemType;
extern const int itemName;
extern const int itemHighlight;

class StationItem : public QGraphicsEllipseItem {   //普通站继承自QGraphics椭圆
public:
    static const int myType = 1;//用于设置该item的itemType
    StationItem(int x, int y);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

class TransferItem : public QGraphicsSvgItem {   //换乘站导入SVG图标
public:
    static const int myType = 1;
    TransferItem(int x, int y);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

class TransparentMaskItem : public QGraphicsRectItem {
public:
    TransparentMaskItem(QGraphicsScene *scene);
};

extern QGraphicsItemGroup* stationGroup;
extern QGraphicsItemGroup* highlightGroup;

#endif // ITEM_H
