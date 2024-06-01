#ifndef ITEM_H
#define ITEM_H

#include "class.h"

#include <QColor>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QtSvgWidgets/QGraphicsSvgItem>

extern const int itemType;
extern const int itemName;
extern const int itemHighlight;

class StationItem : public QGraphicsEllipseItem {   //普通站继承自QGraphics椭圆
public:
    static const int myType = 1;    //用于setData中设置该item的itemType
    StationItem(int x, int y);
};
class TransferItem : public QGraphicsSvgItem {   //换乘站导入SVG图标
public:
    static const int myType = 1;
    TransferItem(int x, int y);
};

class TrainItem : public QGraphicsSvgItem {   //
public:
    TrainItem(int x, int y);
};

class TransparentMaskItem : public QGraphicsRectItem {
public:
    TransparentMaskItem(QGraphicsScene *scene);
    ~TransparentMaskItem();
private:
    QGraphicsScene* scene_;
};


class LinePart:public QGraphicsItemGroup{//对于一个站，每条线是一个模块
public:
    QGraphicsTextItem*  lnName;//线路名称
    QColor lnColor;//线路颜色
    QGraphicsTextItem* stPlus;
    QGraphicsTextItem* stDeduct;
    QGraphicsTextItem* stPlusShou;
    QGraphicsTextItem* stPlusMo;
    QGraphicsTextItem* stDeductShou;
    QGraphicsTextItem* stDeductMo;
    LinePart(int x,int y,int lineNum);
};

class LableItem: public QGraphicsItemGroup{//鼠标放置时显示的标签
public:
    int sx,sy;//作为lable绘图标准的x，y，标定左上角的位置
    int height=20,width=100;
    int lineNum;//统计这个站是几条线的交点
    Station* stn; //站点的指针，这个指针可能需要遍历很多次
    QGraphicsRectItem* frame;//框架
    QGraphicsTextItem* staName;//lable的最高处，本站站名，统一使用北京地铁颜色
    QGraphicsTextItem* shou;
    QGraphicsTextItem* mo;
    QVector<LinePart*> lineInfo;//lable的每一个模块，用一个vector表示，代表换乘线的信息，模块与模块之间从上到下排列
    LableItem(int x,int y,QString stName);
};

#endif // ITEM_H
