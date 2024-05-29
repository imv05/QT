#include "global.h"
#include "paintmain.h"
#include "class.h"
#include "item.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <cmath>
//直径：换乘站40，非换乘站26，线条粗16，典型站间距横向95，纵向57。字体高27
QVector<QGraphicsTextItem*> numberItemList; //用于显示到达各站的时间
const qreal PATH_ZVALUE = -10;  //层叠关系：path线条位于-10
const qreal PATH_WIDTH = 12;    //path粗
const qreal PATH_RADIUS = 40;   //path弯角半径
const qreal MINIMUM = 15;   //最小锚点间距，小于此值将减少半径处理
QPointF normalize(QPointF a){
    double length = sqrt(pow(a.x(),2)+pow(a.y(),2));
    return QPointF(a.x()/length, a.y()/length);
}
qreal absoluteAngle(QPointF point){ //返回给定点（向量）从x轴正方向开始的方位角
    if (point.x() == 0 && point.y() == 0) {
        return 0.0;
    }
    double angleInRadians = std::atan2(-point.y(), point.x());//注意y的正方向不同
    double angleInDegrees = angleInRadians * 180.0 / acos(-1.);
    if (angleInDegrees < 0) {
        angleInDegrees += 360.0;
    }
    return angleInDegrees;
}
QPointF calculateCenter(QPointF pc, QPointF p1, QPointF p2, qreal radius, qreal& retSAngle, qreal& retSpan){
    QPointF p1pcunit = normalize(QPointF((pc.x()-p1.x()), (pc.y()-p1.y())));
    QPointF p2pcunit = normalize(QPointF((pc.x()-p2.x()), (pc.y()-p2.y())));
    // QPointF popcunit = normalize(p1pcunit + p2pcunit);
    QPointF h1ounit;
    qreal dtprdt = QPointF::dotProduct(p1pcunit, p2pcunit); //计算点乘，即为顶角cos值
    qreal wedge = p1pcunit.x()*p2pcunit.y()-p1pcunit.y()*p2pcunit.x();  //计算叉乘，为负，则1-c-2为右转
    if(dtprdt>0.99){//如果p1-pc-p2几乎是直线
        retSAngle = 0;
        retSpan = 0;
        return pc;
    }
    qreal hclength = radius*sqrt((1+dtprdt)/(1-dtprdt));
    QPointF ph1 = pc-p1pcunit*hclength;
    if(wedge < 0){  //注意，xy平面为左手系
        h1ounit = QPointF(-1*p1pcunit.y(), p1pcunit.x());
        retSAngle = absoluteAngle(h1ounit*-1);
        retSpan = -(180-acos(dtprdt)*180/acos(-1));
        qDebug()<< pc.x() << pc.y() << p1.x()<<p1.y()<< p2.x()<<p2.y() << radius << retSAngle << retSpan;
    }else{
        h1ounit = QPointF(p1pcunit.y(), -1*p1pcunit.x());
        retSAngle = absoluteAngle(h1ounit*-1);
        retSpan = (180-acos(dtprdt)*180/acos(-1));
    }
    QPointF po = ph1+h1ounit*radius;
    return po;
}

void paintLine(QGraphicsScene& sc, Line* cLine){
    QFont stationFont("黑体", 20);
    for(auto it: cLine->stationMap){
        QPen pen(Qt::white);
        pen.setWidth(1);
        Station* stn = it;
        int x = stn->x;
        int y = stn->y;
        if(stn->iCnt){  //换乘站
            stn->item = (new TransferItem(x, y));
            it->item->setData(itemType, TransferItem::myType);
            sc.addItem(stn->item);
        }else{  //非换乘站
            stn->item = (new StationItem(x, y));
            it->item->setData(itemType, StationItem::myType);
            sc.addItem(stn->item);
        }
        it->item->setData(itemName, it->stationName);
        it->textItem = sc.addText(it->stationName);
        //以下为检测碰撞并在可选站名显示区域（车站绕一周）选择合适的地方显示
        const qreal M = stn->iCnt?20:14;
        const qreal H = it->textItem->boundingRect().height();
        const qreal W = it->textItem->boundingRect().width();
        qDebug() << it->stationName << "height:" << it->textItem->boundingRect().height() <<
            it->textItem->boundingRect().width();
        qreal xAlternatives[8] = {x+M, x+M, x+M, x-W/2, x-M-W, x-M-W, x-M-W, x-W/2};
        qreal yAlternatives[8] = {y-H/2, y+M, y-M-H, y-M-H, y-M-H, y-H/2, y+M, y+M};
        int k=0; bool ok = false; int minCollide = 100;
        for(k=0; k<8; k++){
            it->textItem->setPos(xAlternatives[k], yAlternatives[k]);
            int collisionCnt = it->textItem->collidingItems().size();
            qDebug() << it->stationName << k << collisionCnt;
            if(collisionCnt==0){
                ok = true;
                break;
            }
            if(collisionCnt < minCollide)minCollide = collisionCnt;
        }
        if(!ok){
            for(k=0; k<8; k++){
                it->textItem->setPos(xAlternatives[k], yAlternatives[k]);
                int collisionCnt = it->textItem->collidingItems().size();
                if(minCollide == collisionCnt){
                    qDebug() << it->stationName << k << collisionCnt;
                    break;
                }
            }
        }
        it->textItem->setFont(stationFont);
        it->textItem->setDefaultTextColor(Qt::black);
        it++;
    }
}
void paintMain(QGraphicsScene& sc){

    QMap<QPair<Station*, Station*>, SPath*>::iterator spit = spathMap.begin();
    qreal radius = PATH_RADIUS;
    for(; spit!=spathMap.end(); spit++){
        Station* fromStn = spit.key().first;
        Line* cLine = fromStn->line;
        QPen pathPen = QPen(cLine->color, PATH_WIDTH);   //线条使用线路标识色
        SPath* sp = spit.value();
        QPainterPath qpp;
        qpp.moveTo(sp->start);  //从起点出发
        int cornerCnt = sp->corner.size();
        for(int i=0; i<cornerCnt; i++){
            QPointF p1, p2; //该corner的前后两个点
            if(i==0)p1 = sp->start;
            else p1 = sp->corner[i-1];
            if(i==cornerCnt-1)p2 = sp->end;
            else p2 = sp->corner[i+1];
            if((sp->corner[i]-p1).manhattanLength()<MINIMUM){
                radius = MINIMUM;
            }
            if((sp->corner[i]-p2).manhattanLength()<MINIMUM){
                radius = MINIMUM;
            }
            qreal sAngle, span;
            QPointF pcenter = calculateCenter(sp->corner[i], p1, p2, radius, sAngle, span);
            QRectF boundingRect = QRectF(pcenter-QPointF(radius,radius), pcenter+QPointF(radius,radius));
            qpp.arcTo(boundingRect, sAngle, span);
        }
        qpp.lineTo(sp->end);    //连接终点
        QGraphicsPathItem* pitem = sc.addPath(qpp, pathPen);
        pitem->setZValue(PATH_ZVALUE);
        cLine->pathItemList.push_back(pitem);
    }
    for(auto it: lineMap){
        paintLine(sc, it);
        it++;
    }
}
void paintTime(QGraphicsScene& sc, std::unordered_map<Station*, int> timeMap){
    for(auto sit: allStationNames){
        numberItemList.push_back(sc.addText(QString::number(timeMap[sit]/60)));
        auto nitem = numberItemList.back();
        nitem->setPos(sit->item->pos());
        nitem->setFont(QFont("微软雅黑", 10));
    }
}
void clearTime(QGraphicsScene& sc){
    for(auto it: numberItemList){
        sc.removeItem(it);
        delete it;
    }
    numberItemList.clear();
}
