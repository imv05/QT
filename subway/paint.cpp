#include "global.h"
#include "class.h"
#include "item.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

void paintLine(QGraphicsScene& sc, Line* cLine){
    QFont stationFont("黑体", 6);
    // textItem->setFont(lineFont);
    // textItem->setDefaultTextColor(lineColor);
    for(auto it: cLine->stationMap){
        QPen pen(Qt::white);
        pen.setWidth(1);
        Station* stn = it;
        int x = stn->x;
        int y = stn->y;
        if(stn->iCnt){  //如果是换乘站
            stn->item = (new transferItem(x, y));
            it->item->setData(itemType, transferItem::myType);
            sc.addItem(stn->item);
        }else{
            stn->item = (new stationItem(x, y));
            it->item->setData(itemType, stationItem::myType);
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
