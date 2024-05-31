#include "global.h"
#include "paintplan.h"
#include "item.h"
#include "search.h"
#include "class.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

void paintPlan(QGraphicsScene& pr){
    //调用search.h中的static QVector<Station*> planRoute;来获取路径规划中的站点信息
    //后续补充：画的是没有展开的版本
    pr.clear();
    QFont stationFont("微软雅黑", 10);
    int i;
    int packedsize=0;
    int x=30,y=10;//绘制文字的坐标，其中x保持40，y每打印一个就+20
    int plansize=Plan::planRoute.size();//整个规划出的路径的vector的大小
    QVector<Station*> packedRoute;//重新用一个数组标记折叠起来的站点名称
    QVector<QGraphicsTextItem*>  packedItem;
    QVector<QGraphicsTextItem*>  lineTextItem;
    QVector<QGraphicsRectItem*>  lineItem;
    QVector<TrainItem*>  trainItem;


    packedRoute.push_back(Plan::planRoute[0]);//起点
    TrainItem* tmp=new TrainItem(x,y);
    trainItem.push_back(tmp);x+=20;
    pr.addItem(trainItem[0]);
    packedItem.push_back(pr.addText(packedRoute[0]->stationName));
    packedItem[0]->setPos(x, y);x-=20;
    packedItem[0]->setFont(stationFont);
    packedItem[0]->setDefaultTextColor(Qt::black);//加入画图
    QGraphicsRectItem* tmprect=new QGraphicsRectItem;
    lineItem.push_back(tmprect);
    lineItem[0]=pr.addRect(QRectF(x+11,y+21,4,38),QPen(packedRoute[0]->line->color),QBrush(packedRoute[0]->line->color));
    QGraphicsTextItem* tmptext=new QGraphicsTextItem;
    lineTextItem.push_back(tmptext);
    lineTextItem[0]=pr.addText(Plan::planRoute[0]->line->lineName);
    lineTextItem[0]->setPos(x+16,y+28);
    lineTextItem[0]->setFont(stationFont);
    lineTextItem[0]->setDefaultTextColor(Plan::planRoute[0]->line->color);
    packedsize++;y+=60;

    for(i=1;i<plansize-1;i++){//遍历原始规划信息
        if(Plan::planRoute[i]->stationName==Plan::planRoute[i+1]->stationName){//和下一个一样，说明在这个站会发生换乘动作
            packedRoute.push_back(Plan::planRoute[i]);
            tmp=new TrainItem(x,y);
            trainItem.push_back(tmp);x+=20;
            pr.addItem(trainItem[packedsize]);
            packedItem.push_back(pr.addText(packedRoute[packedsize]->stationName));
            packedItem[packedsize]->setPos(x, y);x-=20;
            packedItem[packedsize]->setFont(stationFont);
            packedItem[packedsize]->setDefaultTextColor(Qt::black);//加入画图
            tmprect=new QGraphicsRectItem;
            lineItem.push_back(tmprect);
            lineItem[packedsize]=pr.addRect(QRectF(x+11,y+21,4,38),QPen(Plan::planRoute[i+1]->line->color),QBrush(Plan::planRoute[i+1]->line->color));
            tmptext=new QGraphicsTextItem;

            lineTextItem.push_back(tmptext);
            lineTextItem[packedsize]=pr.addText(Plan::planRoute[i+1]->line->lineName);
            lineTextItem[packedsize]->setPos(x+16,y+28);
            lineTextItem[packedsize]->setFont(stationFont);
            lineTextItem[packedsize]->setDefaultTextColor(Plan::planRoute[i+1]->line->color);
            packedsize++;y+=60;
        }
    }
    packedRoute.push_back(Plan::planRoute[plansize-1]);//终点
    tmp=new TrainItem(x,y);
    trainItem.push_back(tmp);x+=20;
    pr.addItem(trainItem[packedsize]);
    packedItem.push_back(pr.addText(packedRoute[packedsize]->stationName));
    packedItem[packedsize]->setPos(x, y);
    packedItem[packedsize]->setFont(stationFont);
    packedItem[packedsize]->setDefaultTextColor(Qt::black);//加入画图
    packedsize++;//完成站点提取，此时，packedsize为待输出的路线的站点名称集合（首+换乘+尾）
}
