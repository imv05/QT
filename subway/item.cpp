#include "item.h"
#include <QGraphicsScene>
#include <QDebug>

StationItem::StationItem(int x, int y): QGraphicsEllipseItem(0, 0, 6, 6) {
    setPos(x-3, y-3);
}
void StationItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse entered the item";
}
void StationItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse left the item";
}

TransferItem::TransferItem(int x, int y): QGraphicsSvgItem(":/images/src/turn.svg") {
    setPos(x-5, y-5);//此处给定左上角坐标
}
void TransferItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse entered the transfer item";
}
void TransferItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse left the transfer item";
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
