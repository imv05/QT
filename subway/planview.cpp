#include "planview.h"
#include "item.h"
#include "paintplan.h"

#include <QMessageBox>
#include <QDebug>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QMessageBox>
#include <QGraphicsItem>

PlanGraphicsView::PlanGraphicsView(QGraphicsScene& scene, QWidget *parent)
    : QGraphicsView(parent),scene_(scene){

}

void PlanGraphicsView::mousePressEvent(QMouseEvent *event){
    int i;
    QPointF scenePos = mapToScene(event->pos()); // 转换坐标
    if (event->button() == Qt::LeftButton){
        QList<QGraphicsItem*> items = scene_.items(scenePos);
        foreach (QGraphicsItem *item, items) {
            TriangleItem *triangleItem1 = qgraphicsitem_cast<TriangleItem*>(item);
            if (triangleItem1) {
                for(i=0;i<packedsize;i++){
                    if(triangleItem1==triangleItem[i]){ // 即第i个模块的展开/折叠态需要转换
                        if(fold[i]==true) fold[i]=false;
                        else fold[i]=true;
                        break;
                    }
                }
                scene_.clear();
                paintPlan(scene_);
                break; // 不需要检查列表中的其他项，退出循环
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}
