#include "item.h"
#include "class.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QModelIndex>
//直径：换乘站40，非换乘站26，线条粗16，典型站间距横向95，纵向57。字体高27
const int MASK_TYPE = 999;
StationItem::StationItem(int x, int y): QGraphicsEllipseItem(0, 0, 26, 26) {
    setBrush(QBrush(Qt::white));
    setPos(x-13, y-13);
}
TransferItem::TransferItem(int x, int y): QGraphicsSvgItem(":/images/src/turn.svg") {
    setPos(x-20, y-20);//此处给定左上角坐标
    // setScale(double(16/26));
    // setPos(x-8, y-8);
}

TrainItem::TrainItem(int x, int y): QGraphicsSvgItem(":/images/src/train.svg") {
    setPos(x+8, y+7);//此处给定左上角坐标
}
TransparentMaskItem::TransparentMaskItem(QGraphicsScene *scene) : QGraphicsRectItem(scene->sceneRect(), nullptr) {
    scene_ = scene;
    QColor bgcolor = QColor(Qt::white);
    bgcolor.setAlpha(200);
    setBrush(bgcolor);
    setData(itemType, MASK_TYPE);
    setPen(QPen(Qt::NoPen)); // 没有边框
    setZValue(100);  //设置z值，覆盖在原图之上
    scene->addItem((QGraphicsItem*)this);
}
TransparentMaskItem::~TransparentMaskItem(){
    scene_->removeItem((QGraphicsItem*) this);
}

const int itemType = static_cast<int>(Qt::UserRole) + 1;
const int itemName = static_cast<int>(Qt::UserRole) + 2;
const int itemHighlight = static_cast<int>(Qt::UserRole) + 3;

QString transferTime(int sec){//传入以秒为单位的时间，转化为24小时计的字符串
    int hour=0,minute=0;
    QString ret="";
    hour=sec/3600;
    minute=(sec-3600*hour)/60;
    ret+=std::to_string(hour);
    if(ret.length()==1)ret="0"+ret;
    ret+=":";
    ret+=std::to_string(minute);
    if(ret.length()==4)ret.insert(3,"0");
    return ret;
}

LinePart::LinePart(int x,int y,int lineNum,Station* stn){
    QFont stationFont("黑体", 20);
    Line* ln=lineMap[lineNum];//找到当前线路的指针
    QPen lnPen;lnPen.setColor(ln->color);
    lnPen.setWidth(8);
    //画出线的名称
    lnLine=new QGraphicsLineItem(x-24,y-24,x+414,y-24);
    lnLine->setPen(lnPen);
    addToGroup(lnLine);
    lnRect=new QGraphicsRectItem(x-10,y-5,170,45);
    lnRect->setPen(QPen(ln->color));
    lnRect->setBrush(ln->color);
    addToGroup(lnRect);
    lnName=new QGraphicsTextItem(ln->lineName);
    lnName->setPos(x,y);
    lnName->setFont(stationFont);
    lnName->setDefaultTextColor(Qt::white);
    addToGroup(lnName);//线路名称加入
    //模块视图效果：
    //======================
    //线路名   首班车   末班车
    //方向一     T1      T2
    //方向二     T3      T4
    shou=new QGraphicsTextItem("首班车");
    shou->setPos(x+180,y);
    shou->setFont(stationFont);
    shou->setDefaultTextColor(ln->color);
    addToGroup(shou);//首班车标签加入
    mo=new QGraphicsTextItem("末班车");
    mo->setPos(x+300,y);
    mo->setFont(stationFont);
    mo->setDefaultTextColor(ln->color);
    addToGroup(mo);//末班车标签加入
    stPlus=new QGraphicsTextItem(ln->incDirection);
    stPlus->setPos(x,y+50);
    stPlus->setFont(stationFont);
    stPlus->setDefaultTextColor(ln->color);
    addToGroup(stPlus);//站增方向加入
    stDeduct=new QGraphicsTextItem(ln->decDirection);
    stDeduct->setPos(x,y+100);
    stDeduct->setFont(stationFont);
    stDeduct->setDefaultTextColor(ln->color);
    addToGroup(stDeduct);//站增方向加入
    //提取出站增方向的首末班车时间：
    int tmps=0,tmpm=0,found=0;
    for(auto it=stn->cList.begin();it!=stn->cList.end();it++){//遍历clist
        if(it->isTransfer==false && it->direction==1){//不是换乘站且站增方向
            tmps=it->first;tmpm=it->last;found=1;
        }
    }
    if(found==1){
        stPlusShou=new QGraphicsTextItem(transferTime(tmps));
        stPlusShou->setPos(x+200,y+50);
    }
    else if(found==0){
        stPlusShou=new QGraphicsTextItem("-");
        stPlusShou->setPos(x+230,y+50);
    }
    stPlusShou->setFont(stationFont);
    stPlusShou->setDefaultTextColor(ln->color);
    addToGroup(stPlusShou);//站增方向加入
    if(found==1){
        stPlusMo=new QGraphicsTextItem(transferTime(tmpm));
        stPlusMo->setPos(x+300,y+50);
    }
    else if(found==0){
        stPlusMo=new QGraphicsTextItem("-");
        stPlusMo->setPos(x+330,y+50);
    }
    stPlusMo->setFont(stationFont);
    stPlusMo->setDefaultTextColor(ln->color);
    addToGroup(stPlusMo);//站增方向加入
    //提取出站减方向的首末班车时间：
    found=0;
    for(auto it=stn->cList.begin();it!=stn->cList.end();it++){//遍历clist
        if(it->isTransfer==false && it->direction==-1 ){//不是换乘站且站增方向
            tmps=it->first;tmpm=it->last;found=1;
        }
    }
    if(found==1){
        stDeductShou=new QGraphicsTextItem(transferTime(tmps));
        stDeductShou->setPos(x+200,y+100);
    }
    else if(found==0){
        stDeductShou=new QGraphicsTextItem("-");
        stDeductShou->setPos(x+230,y+100);
    }
    stDeductShou->setFont(stationFont);
    stDeductShou->setDefaultTextColor(ln->color);
    addToGroup(stDeductShou);//站增方向加入
    if(found==1){
        stDeductMo=new QGraphicsTextItem(transferTime(tmpm));
        stDeductMo->setPos(x+300,y+100);
    }
    else if(found==0){
        stDeductMo=new QGraphicsTextItem("-");
        stDeductMo->setPos(x+330,y+100);
    }
    stDeductMo->setFont(stationFont);
    stDeductMo->setDefaultTextColor(ln->color);
    addToGroup(stDeductMo);//站增方向加入
}

void LabelItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton)
    {
        // // 假设你已经有一个 MainWindow 指针
        // MainWindow *mainWindow = qobject_cast<MainWindow *>(QApplication::activeWindow());
        // if (mainWindow)
        // {
        //     // 创建一个临时的 QModelIndex，因为 on_listA_clicked 需要一个 QModelIndex 参数
        //     QModelIndex index;
        //     // 调用 MainWindow 的槽函数
        //     mainWindow->on_listA_clicked(index);
        // }
    }
    QGraphicsItemGroup::mousePressEvent(event);
}
//第一套构造函数，适配stationsByName
LabelItem::LabelItem(int x,int y,QString stName){//以x,y为基准，建立起Label对应的图形信息
    this->setData(itemType,myType);
    int i,cur=0;
    QFont stationFont("黑体", 20);
    stn=stationsByName[stName];//获取指向本站的指针
    lineNum=stn.size();//共有几条线经过了本站
    height=20+lineNum*180+110;
    width=450;
    //确定左上角的位置：
    sx=x-width/2;sy=y-height-10;
    //画出框架
    QPen framePen;
    framePen.setColor(Qt::black);
    framePen.setWidth(4);
    frame=new QGraphicsRectItem(sx,sy,width,height);
    frame->setPen(framePen);
    frame->setBrush(Qt::white);
    addToGroup(frame);
    //添加本站名称
    staName=new QGraphicsTextItem(stName);
    staName->setPos(sx+30,sy+20);
    staName->setFont(stationFont);
    staName->setDefaultTextColor(Qt::black);
    addToGroup(staName);
    for(i=0;i<lineNum;i++){//遍历n条线，提取n个模块
        cur=stn[i]->lineId;//当前线路的ID
        lineInfo.push_back(new LinePart(sx+30,sy+100+180*i,cur,stn[i]));
        addToGroup(lineInfo[i]);//初始化模块
    }
    startRect=new QGraphicsRectItem(sx+30,sy+20+lineNum*180+60,160,43);
    startRect->setPen(QPen(Qt::black));
    startRect->setBrush(Qt::blue);
    addToGroup(startRect);
    startRect->setData(114,"start");
    startRect->setData(115,stName);
    //connect(startRect, &QGraphicsRectItem::mousePressEvent, this, &LabelItem::mousePressEvent);
    setstart=new QGraphicsTextItem("设为起点");
    setstart->setFont(stationFont);
    setstart->setDefaultTextColor(Qt::white);
    setstart->setPos(sx+50,sy+20+lineNum*180+65);
    addToGroup(setstart);
    endRect=new QGraphicsRectItem(sx+250,sy+20+lineNum*180+60,160,43);
    endRect->setPen(QPen(Qt::black));
    endRect->setBrush(Qt::blue);
    endRect->setData(114,"end");
    endRect->setData(115,stName);
    addToGroup(endRect);
    setend=new QGraphicsTextItem("设为终点");
    setend->setFont(stationFont);
    setend->setDefaultTextColor(Qt::white);
    setend->setPos(sx+270,sy+20+lineNum*180+65);
    addToGroup(setend);
    this->setZValue(500);
}

