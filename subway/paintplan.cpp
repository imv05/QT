#include "global.h"
#include "paintplan.h"
#include "item.h"
#include "search.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

void paintPlan(QGraphicsScene& pr){
    //调用search.h中的static QVector<Station*> planRoute;来获取路径规划中的站点信息
    pr.clear();
    QFont stationFont("微软雅黑", 10);
    int i;
    int plansize=Plan::planRoute.size();
    int x=30,y=10;//绘制文字的坐标，其中x保持40，y每打印一个就+20
    int nownumber=Plan::planRoute[0]->lineId;
    //标出首个线路编号
    Plan::planRoute[0]->planLiItem=pr.addText(Plan::planRoute[0]->line->lineName);
    Plan::planRoute[0]->planLiItem->setPos(x, y);
    Plan::planRoute[0]->planLiItem->setFont(stationFont);
    Plan::planRoute[0]->planLiItem->setDefaultTextColor(Plan::planRoute[0]->line->color);//加入画图
    x+=10;
    for(i=0;i<plansize;i++){//构建循环“画出”规划出的路径
        if(Plan::planRoute[i]->lineId==nownumber){//如果还停留在当前的线路
            ;
        }else{
            nownumber=Plan::planRoute[i]->lineId;//更新当前线路
            //TODO:标出线路编号，1行
            x-=10;y+=20;
            Plan::planRoute[i]->planLiItem=pr.addText(Plan::planRoute[i]->line->lineName);
            Plan::planRoute[i]->planLiItem->setPos(x, y);
            Plan::planRoute[i]->planLiItem->setFont(stationFont);
            Plan::planRoute[i]->planLiItem->setDefaultTextColor(Plan::planRoute[i]->line->color);//加入画图
            x+=10;
        }
        y+=20;//更新高度
        Plan::planRoute[i]->planStItem=pr.addText(Plan::planRoute[i]->stationName);//加上站名
        Plan::planRoute[i]->planStItem->setPos(x, y);
        Plan::planRoute[i]->planStItem->setFont(stationFont);
        Plan::planRoute[i]->planStItem->setDefaultTextColor(Plan::planRoute[i]->line->color);//加入画图
    }
}
