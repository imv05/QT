#include "item.h"
#include <QDebug>

stationItem::stationItem(int x, int y): QGraphicsEllipseItem(x-3, y-3, 6, 6) {
}
void stationItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse entered the item";
}
void stationItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse left the item";
}

transferItem::transferItem(int x, int y): QGraphicsSvgItem(":/images/src/turn.svg") {
    setPos(x-5, y-5);//此处给定左上角坐标
}
void transferItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse entered the transfer item";
}
void transferItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse left the transfer item";
}
const int itemType = static_cast<int>(Qt::UserRole) + 1;
const int itemName = static_cast<int>(Qt::UserRole) + 2;
const int itemHighlight = static_cast<int>(Qt::UserRole) + 3;
