#ifndef ITEM_H
#define ITEM_H

#include "class.h"
//#include "search.cpp"


#include <QColor>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QtSvgWidgets/QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>

extern const int itemType;
extern const int itemName;
extern const int itemHighlight;

class StationItem : public QGraphicsEllipseItem {   //普通站继承自QGraphics椭圆
public:
    static const int myType = 1;    //用于setData中设置该item的itemType
    StationItem(int x, int y, bool available);
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
    QGraphicsLineItem* lnLine;//线路上方的装饰线
    QGraphicsRectItem* lnRect;//线路的矩形
    QGraphicsTextItem*  lnName;//线路名称
    QColor lnColor;//线路颜色
    QGraphicsTextItem* stPlus;//站增方向
    QGraphicsTextItem* stDeduct;//站减方向
    QGraphicsTextItem* stPlusShou;//站增方向首班车时间
    QGraphicsTextItem* stPlusMo;//站增方向末班车时间
    QGraphicsTextItem* stDeductShou;//站减方向首班车时间
    QGraphicsTextItem* stDeductMo;//站减方向末班车时间
    QGraphicsTextItem* shou;//首班车标签
    QGraphicsTextItem* mo;//末班车标签
    LinePart(int x,int y,int lineNum,Station* stn);
};

class LabelItem: public QGraphicsItemGroup{//鼠标放置时显示的标签
public:
    static const int myType=114;
    int sx,sy;//作为Label绘图标准的x，y，标定左上角的位置
    int height=20,width=100;
    int lineNum;//统计这个站是几条线的交点
    QVector<Station*> stn; //站点的指针，这个指针可能需要遍历很多次
    QGraphicsRectItem* frame;//框架
    QGraphicsTextItem* staName;//Label的最高处，本站站名，统一使用北京地铁颜色
    QGraphicsTextItem* shou;
    QGraphicsTextItem* mo;
    QVector<LinePart*> lineInfo;//Label的每一个模块，用一个vector表示，代表换乘线的信息，模块与模块之间从上到下排列
    QGraphicsTextItem* setstart;
    QGraphicsTextItem* setend;
    QGraphicsRectItem* startRect;
    QGraphicsRectItem* endRect;
    LabelItem(int x,int y,QString stName);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ITEM_H
