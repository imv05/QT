#include "stationitem.h"
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
    setPos(x-5, y-5);
}
void transferItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse entered the transfer item";
}
void transferItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "Mouse left the transfer item";
}
