#include "item.h"
#include "class.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
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
    bgcolor.setAlpha(50);
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

LinePart::LinePart(int x,int y,int lineNum){
    QFont stationFont("黑体", 20);
    Line* ln=lineMap[lineNum];//找到当前线路的指针
    //画出线的名称
    lnName=new QGraphicsTextItem(ln->lineName);
    lnName->setPos(x,y);
    lnName->setFont(stationFont);
    lnName->setDefaultTextColor(ln->color);
    x+=30;
    //TODO:方向1名称



}

LableItem::LableItem(int x,int y,QString stName){//以x,y为基准，建立起lable对应的图形信息
    int i,cur=0;
    QFont stationFont("黑体", 20);
    sx=x;sy=y;//注意：这一行只是先放这里，后面需要调整
    x+=10;y+=10;
    //添加本站名称
    staName=new QGraphicsTextItem(stName);
    staName->setPos(x,y);
    staName->setFont(stationFont);
    staName->setDefaultTextColor(Qt::black);
    addToGroup(staName);
    y+=10;
    //TODO:根据读入的站名获取线路列表和线路数量lineNum


    for(i=0;i<lineNum;i++){//遍历三条线，提取n个模块
        lineInfo.push_back(new LinePart(x,y,cur));
        addToGroup(lineInfo[i]);//初始化模块
        y+=60;
    }

    //添加整体框架
    height=20+lineNum*60+20;
    QPen framePen;
    framePen.setColor(Qt::black);
    framePen.setWidth(4);
    frame=new QGraphicsRectItem(sx,sy,height,width);
    frame->setPen(framePen);
    addToGroup(frame);

}
