#include "realtimeclass.h"
#include "realtimeview.h"

rtTextItem::rtTextItem(QString qs):QGraphicsTextItem(qs){}


void rtTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "clicked" << this->data(150);
    QGraphicsScene* sc = this->scene();
    QGraphicsView* view = this->scene()->views().at(0);
    // sc->addText();
}

void rtTextItem::hoverEnterEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsView *view = this->scene()->views().at(0);
    view->setCursor(Qt::OpenHandCursor);
    qDebug() << "e";
}

void rtTextItem::hoverLeaveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsView *view = this->scene()->views().at(0);
    view->viewport()->setCursor(Qt::ArrowCursor);
    view->viewport()->update();
    qDebug() << "l";
}
