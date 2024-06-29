#include "global.h"
#include "paintplan.h"
#include "item.h"
#include "search.h"
#include "class.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QMouseEvent>

class MyTriangleItem : public QGraphicsPolygonItem {
public:
    MyTriangleItem(const QPolygonF &polygon, QGraphicsItem *parent = nullptr)
        : QGraphicsPolygonItem(polygon, parent) {
        // 设置标志，使项目可选并可接受鼠标事件
        setFlag(QGraphicsItem::ItemIsSelectable, true);
        setAcceptHoverEvents(true);
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        // 在这里处理鼠标按下事件
        if (event->button() == Qt::LeftButton) {
            // 鼠标左键被按下，执行特定操作
            qDebug() << "Triangle clicked!";
            // 你可以改变项目的颜色、形状等
            setPen(QPen(Qt::red));
        }
        // 调用基类的事件处理方法，如果需要的话
        QGraphicsPolygonItem::mousePressEvent(event);
    }
};

QVector<Station*> compareRoute;//用于对比规划线路是否产生了变化，
//如果没有变化，就是折叠态发生了变化；如果有变化，就是路径存在变化
QVector<Station*> packedRoute;//重新用一个数组标记折叠起来的站点名称
QVector<QString> packedText;    //折叠后仍然显示的站点所处的字符串，例如“海淀黄庄 站台-站厅通道换乘 2分钟”
QVector<QGraphicsTextItem*> packedItem;
QVector<QString> lineText;  //线路显示，例如“13号线”
QVector<QString> directionText; //方向显示，例如“东直门方向”
QVector<QGraphicsTextItem*> lineTextItem;
QVector<QPolygonF*> trianglePaint;//存储折叠三角形的形状信息
bool fold[50];//用于判断当前模块是折叠态还是展开态
QVector<TriangleItem *> triangleItem;//展示折叠的三角形，和线路名称一同出现
QVector<QGraphicsTextItem*> directionItem;
QVector<QGraphicsRectItem*> lineItem;
QVector<TrainItem*> trainItem;
QVector<QVector<QGraphicsTextItem*>> expandText;//展开态的站点信息

int x=5,y=40;//x,y定位模块的位置信息
int packedsize=0;

void paintFolded(QGraphicsScene& pr,int num){//负责画一个折叠的模块
    //折叠模块：纵向长度固定为60
    //num传入的信息为第几个模块
    QFont stationFont("微软雅黑", 10);
    expandText.push_back(QVector<QGraphicsTextItem*>());//填入空vector，只占位，在此处用不到
    expandText[packedsize].push_back(nullptr);
    packedRoute.push_back(Plan::planRoute[num+1]);//填入路径规划信息
    TrainItem* tmp=new TrainItem(x,y);
    trainItem.push_back(tmp);
    x+=20;
    pr.addItem(trainItem[packedsize]);
    packedItem.push_back(pr.addText(packedRoute[packedsize]->stationName));
    packedItem[packedsize]->setPos(x, y);
    x-=20;
    packedItem[packedsize]->setFont(stationFont);
    packedItem[packedsize]->setDefaultTextColor(Qt::black);//加入画图
    lineItem.push_back(nullptr);
    lineItem[packedsize]=pr.addRect(QRectF(x+11,y+21,4,38),QPen(Plan::planRoute[num+1]->line->color),QBrush(Plan::planRoute[num+1]->line->color));
    lineTextItem.push_back(nullptr);
    lineTextItem[packedsize]=pr.addText(lineText[packedsize], stationFont);
    lineTextItem[packedsize]->setPos(x+30,y+19);
    lineTextItem[packedsize]->setFont(stationFont);
    lineTextItem[packedsize]->setDefaultTextColor(Plan::planRoute[num+1]->line->color);
    trianglePaint.push_back(new QPolygonF);
    triangleItem.push_back(nullptr);
    (*trianglePaint[packedsize]) << QPointF(x+25, y+34)       // 顶点
                          << QPointF(x+30, y+29)       // 右侧底角
                          << QPointF(x+20, y+29);      // 左侧底角
    triangleItem[packedsize]=static_cast<TriangleItem*>(pr.addPolygon(*trianglePaint[packedsize]));
    triangleItem[packedsize]->setBrush(Qt::black);
    directionItem.push_back(nullptr);
    directionItem[packedsize]=pr.addText(directionText[packedsize], stationFont);
    directionItem[packedsize]->setPos(x+16,y+36);
    directionItem[packedsize]->setDefaultTextColor(Qt::black);
    packedsize++;//此处为起到控制作用的全局变量
    y+=60;//纵向坐标增加60
}
void paintExpand(QGraphicsScene& pr,int num){//负责画一个展开的模块
    //展开模块：纵向长度不固定，按照站点数量进行延伸
    //num传入的信息为第几个模块
    //线路的获取方式为 planRouteSplit[packedsize]
    QFont stationFont("微软雅黑", 10);
    int i;
    int stnNum=Plan::planRouteSplit[packedsize].size()-2;//代表了需要展开的站点的数量
    expandText.push_back(QVector<QGraphicsTextItem*>());//填入空vector
    packedRoute.push_back(Plan::planRoute[num+1]);//填入路径规划信息
    TrainItem* tmp=new TrainItem(x,y);
    trainItem.push_back(tmp);
    x+=20;
    pr.addItem(trainItem[packedsize]);
    packedItem.push_back(pr.addText(packedRoute[packedsize]->stationName));
    packedItem[packedsize]->setPos(x, y);
    x-=20;
    packedItem[packedsize]->setFont(stationFont);
    packedItem[packedsize]->setDefaultTextColor(Qt::black);//加入画图
    lineItem.push_back(nullptr);
    //区别1：左侧美化矩形的高度，随stnNum的变化而变化
    lineItem[packedsize]=pr.addRect(QRectF(x+11,y+21,4,38+stnNum*15),QPen(Plan::planRoute[num+1]->line->color),QBrush(Plan::planRoute[num+1]->line->color));
    lineTextItem.push_back(nullptr);
    lineTextItem[packedsize]=pr.addText(lineText[packedsize], stationFont);
    lineTextItem[packedsize]->setPos(x+30,y+19);
    lineTextItem[packedsize]->setFont(stationFont);
    lineTextItem[packedsize]->setDefaultTextColor(Plan::planRoute[num+1]->line->color);
    trianglePaint.push_back(new QPolygonF);
    triangleItem.push_back(nullptr);
    (*trianglePaint[packedsize]) << QPointF(x+25, y+34)       // 顶点
                                 << QPointF(x+30, y+29)       // 右侧底角
                                 << QPointF(x+20, y+29);      // 左侧底角
    triangleItem[packedsize]=static_cast<TriangleItem*>(pr.addPolygon(*trianglePaint[packedsize]));
    triangleItem[packedsize]->setBrush(Qt::black);
    directionItem.push_back(nullptr);
    directionItem[packedsize]=pr.addText(directionText[packedsize], stationFont);
    directionItem[packedsize]->setPos(x+16,y+36);
    directionItem[packedsize]->setDefaultTextColor(Qt::black);
    //截止这里，和fold的版本是一样的，下方为不一样的部分
    for(i=0;i<stnNum;i++){
        expandText[packedsize].push_back(nullptr);
        expandText[packedsize][i]=pr.addText(" -"+Plan::planRouteSplit[packedsize][i+1]->stationName,stationFont);
        expandText[packedsize][i]->setPos(x+16,y+51+i*15);
        expandText[packedsize][i]->setFont(stationFont);
        expandText[packedsize][i]->setDefaultTextColor(Qt::black);
    }//维护当前的展开信息vector
    packedsize++;//此处为起到控制作用的全局变量
    y+=60+stnNum*15;//纵向坐标增加60
}

void paintPlan(QGraphicsScene& pr){
    //调用search.h中的static QVector<Station*> planRoute;来获取路径规划中的站点信息
    pr.clear();
    if(compareRoute==Plan::planRoute){//路径没有变化，折叠态已经被调整，其余不变
        ;//保持原先的折叠态不变
    }
    else{
        compareRoute.clear();
        memset(fold,true,sizeof(fold));//初始化统一定为折叠态
        for(int j=0;j<Plan::planRoute.size();j++){
            compareRoute.push_back(Plan::planRoute[j]);
        }//维护新的compareRoute
    }
    //清空所有全局的vector，为模块化输出做准备
    packedRoute.clear();
    packedText.clear();
    packedItem.clear();
    lineText.clear();
    directionText.clear();
    lineTextItem.clear();
    trianglePaint.clear();
    triangleItem.clear();
    directionItem.clear();
    lineItem.clear();
    trainItem.clear();
    expandText.clear();
    packedsize=0;
    x=5,y=40;
    //覆盖一个白色的矩形背景
    // QGraphicsRectItem* back=pr.addRect(0,0,1000,3000);
    // back->setBrush(Qt::white);
    // back->setZValue(-5);
    //总体的字体设置
    QFont stationFont("微软雅黑", 10);
    int i;

    //对于本次路径规划的头部信息
    QGraphicsTextItem* header1 = pr.addText("共计"+QString::number(Plan::planTotalSections)+"站", stationFont);
    header1->setPos(x+20, y-30);
    header1->setDefaultTextColor(Qt::black);
    QGraphicsTextItem* header2 = pr.addText(QString::number(Plan::planTotalTime/60)+"分钟", stationFont);
    header2->setPos(x+80, y-30);
    header2->setDefaultTextColor(Qt::black);

    //整个规划出的路径的vector的大小
    int plansize=Plan::planRoute.size();
    //方案涉及的线路数量
    int lineCnt = Plan::planLines.size();

    //开始维护各种vec中的备选项
    //维护 lineText & triangles
    for(int i=0; i<lineCnt; i++){
        QString currentLineText = Plan::planLines[i]->lineName;
        lineText.push_back(currentLineText);
    }
    //维护 directionText
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
    //维护 packedText
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
    //完成维护，接下来的绘制需要分开进行

    //数量关系：packedText.size() == lineCnt + 1

    if(fold[0]==true) paintFolded(pr,-1);
    else paintExpand(pr,-1);//绘制第一部分

    for(i=0;i<plansize-1;i++){//遍历原始规划信息
        if(Plan::planRoute[i]->lineId!=Plan::planRoute[i+1]->lineId){//和下一个一样，说明在这个站会发生换乘动作
            if(fold[packedsize]==true) paintFolded(pr,i);
            else paintExpand(pr,i);
        }
    }

    //下方为终点的绘制，终点绘制的特殊性在于，只涉及本次路径规划的最终站点，不涉及后续连带的线路信息
    packedRoute.push_back(Plan::planRoute[plansize-1]);//终点
    TrainItem* tmp=new TrainItem(x,y);
    trainItem.push_back(tmp);x+=20;
    pr.addItem(trainItem[packedsize]);
    packedItem.push_back(pr.addText(packedRoute[packedsize]->stationName));
    packedItem[packedsize]->setPos(x, y);
    packedItem[packedsize]->setFont(stationFont);
    packedItem[packedsize]->setDefaultTextColor(Qt::black);//加入画图
    packedsize++;//完成站点提取，此时，packedsize为待输出的路线的站点名称集合（首+换乘+尾）
}
