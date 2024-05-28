#include "global.h"
#include "paintmain.h"
#include "item.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
//直径：换乘站40，非换乘站26，线条粗16，典型站间距横向95，纵向57。字体高27
QVector<QGraphicsTextItem*> numberItemList;
void paintLine(QGraphicsScene& sc, Line* cLine){
    QFont stationFont("微软雅黑", 27);
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
        it->textItem->setPos(x, y);
        it->textItem->setFont(stationFont);
        it->textItem->setDefaultTextColor(Qt::black);
        it++;
    }
}
void paintMain(QGraphicsScene& sc){
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
