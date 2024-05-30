#include "item.h"
#include <QGraphicsScene>
#include <QDebug>
//直径：换乘站40，非换乘站26，线条粗16，典型站间距横向95，纵向57。字体高27
StationItem::StationItem(int x, int y): QGraphicsEllipseItem(0, 0, 26, 26) {
    setBrush(QBrush(Qt::white));
    setPos(x-13, y-13);
}
TransferItem::TransferItem(int x, int y): QGraphicsSvgItem(":/images/src/turn.svg") {
    setPos(x-20, y-20);//此处给定左上角坐标
    // setScale(double(16/26));
    // setPos(x-8, y-8);
}

TrainItem::TrainItem(int x, int y): QGraphicsSvgItem(":/images/src/train1.svg") {
    setPos(x+8, y+7);//此处给定左上角坐标
}
TransparentMaskItem::TransparentMaskItem(QGraphicsScene *scene) : QGraphicsRectItem(scene->sceneRect(), nullptr) {
    QColor bgcolor = QColor(Qt::white);
    bgcolor.setAlpha(50);
    setBrush(bgcolor);
    setPen(QPen(Qt::NoPen)); // 没有边框
    setZValue(100);  //设置z值，覆盖在原图之上
}

const int itemType = static_cast<int>(Qt::UserRole) + 1;
const int itemName = static_cast<int>(Qt::UserRole) + 2;
const int itemHighlight = static_cast<int>(Qt::UserRole) + 3;
