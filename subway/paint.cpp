#include "global.h"
#include "class.h"
#include "item.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

void paintLine(QGraphicsScene& sc, Line* cLine){
    QFont stationFont("黑体", 6);
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
void paint(QGraphicsScene& sc){
    for(auto it: lineMap){
        paintLine(sc, it);
        it++;
    }
}
void paintTime(std::unordered_map<Station*, int> timeMap){

}
