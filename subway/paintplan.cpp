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
    int x=5,y=40;//绘制文字的坐标，其中x保持40，y每打印一个就+20

    QGraphicsTextItem* header1 = pr.addText("共计"+QString::number(Plan::planTotalSections)+"站", stationFont);
    header1->setPos(x+20, y-30);
    QGraphicsTextItem* header2 = pr.addText(QString::number(Plan::planTotalTime/60)+"分钟", stationFont);
    header2->setPos(x+80, y-30);

    int plansize=Plan::planRoute.size();//整个规划出的路径的vector的大小
    QVector<Station*> packedRoute;//重新用一个数组标记折叠起来的站点名称
    QVector<QString> packedText;    //折叠后仍然显示的站点所处的字符串，例如“海淀黄庄 站台-站厅通道换乘 2分钟”
    QVector<QGraphicsTextItem*> packedItem;
    QVector<QString> lineText;  //线路显示，例如“13号线”
    QVector<QString> directionText; //方向显示，例如“东直门方向”
    QVector<QGraphicsTextItem*> lineTextItem;
    QVector<QGraphicsTextItem*> directionItem;
    QVector<QGraphicsRectItem*> lineItem;
    QVector<TrainItem*>  trainItem;
    int lineCnt = Plan::planLines.size();   //方案涉及的线路数量
    //维护lineText
    for(int i=0; i<lineCnt; i++){
        QString currentLineText = Plan::planLines[i]->lineName;

        lineText.push_back(currentLineText);
    }
    //维护directionText
    for(int i=0; i<lineCnt; i++){
        QString currentDirectionText;
        if(Plan::directionOfLine[i] == 1){//如果站增
            currentDirectionText = Plan::planLines[i]->incDirection;
        }else{
            currentDirectionText = Plan::planLines[i]->decDirection;
        }
        currentDirectionText += QString(" ");
        currentDirectionText += QString::number(Plan::planRouteSplit[i].size()-1) + QString("站 ");
        currentDirectionText += QString::number(Plan::timeOfLine[i]/60) + QString("分钟");
        directionText.push_back(currentDirectionText);
    }
    //维护packedText
    packedText.push_back(QString(Plan::planRoute[0]->stationName));
    for(int i=0; i<lineCnt; i++){
        Station* transferAt = Plan::planRouteSplit[i].back();   //每个分线的最后一个站
        QString currentPackedText = transferAt->stationName;
        if(i!=lineCnt-1){ //添加换乘详情注释
            currentPackedText += QString(" ");
            currentPackedText += Plan::transferConnections[i].note;
            currentPackedText += QString::number(Plan::transferConnections[i].time/60);
            currentPackedText += QString("分钟");
        }
        packedText.push_back(currentPackedText);
    }
    //数量关系：packedText.size() == lineCnt + 1
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
    lineTextItem[0]->setPos(x+16,y+20);
    lineTextItem[0]->setFont(stationFont);
    lineTextItem[0]->setDefaultTextColor(Plan::planRoute[0]->line->color);

    directionItem.push_back(nullptr);
    directionItem[packedsize]=pr.addText(directionText[packedsize], stationFont);
    directionItem[packedsize]->setPos(x+16,y+34);
    directionItem[packedsize]->setDefaultTextColor(Qt::black);
    packedsize++;y+=60;
    for(i=0;i<plansize-1;i++){//遍历原始规划信息
        if(Plan::planRoute[i]->lineId!=Plan::planRoute[i+1]->lineId){//和下一个一样，说明在这个站会发生换乘动作
            packedRoute.push_back(Plan::planRoute[i]);
            tmp=new TrainItem(x,y);
            trainItem.push_back(tmp);x+=20;
            pr.addItem(trainItem[packedsize]);
            packedItem.push_back(pr.addText(packedText[packedsize]));
            packedItem[packedsize]->setPos(x, y);x-=20;
            packedItem[packedsize]->setFont(stationFont);
            packedItem[packedsize]->setDefaultTextColor(Qt::black);//加入画图
            lineItem.push_back(nullptr);
            lineItem[packedsize]=pr.addRect(QRectF(x+11,y+21,4,38),QPen(Plan::planRoute[i+1]->line->color),QBrush(Plan::planRoute[i+1]->line->color));
            lineTextItem.push_back(nullptr);
            lineTextItem[packedsize]=pr.addText(lineText[packedsize], stationFont);
            lineTextItem[packedsize]->setPos(x+16,y+20);
            lineTextItem[packedsize]->setDefaultTextColor(Plan::planRoute[i+1]->line->color);
            directionItem.push_back(nullptr);
            directionItem[packedsize]=pr.addText(directionText[packedsize], stationFont);
            directionItem[packedsize]->setPos(x+16,y+34);
            directionItem[packedsize]->setDefaultTextColor(Qt::black);
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
