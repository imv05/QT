#include "mouse.h"

#include<QGraphicsView>
#include <QWheelEvent>
#include <QMessageBox>
#include <QGraphicsItem>

CustomGraphicsView::CustomGraphicsView(QGraphicsScene& scene, QWidget *parent)
        : QGraphicsView(parent), isDragging(false), scene_(scene){
    setMouseTracking(true); // 开启鼠标跟踪
};
// 重写鼠标按下事件
void CustomGraphicsView::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton) {
        // 记录当前鼠标位置
        lastMousePos = event->pos();
        // 设置为正在拖动状态
        isDragging = true;
        // 设置鼠标抓手形状
        setCursor(Qt::ClosedHandCursor);
    }
    else{
        // 将鼠标事件转换为场景坐标
        QPointF scenePos = mapToScene(event->pos());

        // 检查每个形状对象是否被点击
        for (QGraphicsItem *item : scene_.items(scenePos)) {
            if (item->type() == QGraphicsEllipseItem::Type) {
                // 获取圆形形状对象的注释内容
                QString annotation = item->data(Qt::UserRole).toString();
                // 弹出包含注释内容的消息框
                QMessageBox::information(this, "title", annotation);
                return;
            }
        }

    }
    QGraphicsView::mousePressEvent(event);
}
// 重写鼠标移动事件
void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (isDragging) {
        // 计算鼠标移动的距离
        QPoint delta = event->pos() - lastMousePos;
        // 平移视图
        translate(delta.x(), delta.y());
        // 更新上次鼠标位置
        lastMousePos = event->pos();
    }
    else{
        QGraphicsView::mouseMoveEvent(event);
        // 将鼠标位置转换为场景坐标
        QPointF scenePos = mapToScene(event->pos());
        // 检查是否在点的范围内
        QGraphicsScene* scene = this->scene();
        if (scene) {
            bool foundPoint = false; // 用于标记是否找到了点
            QString name;
            QList<QGraphicsItem*> items = scene->items(scenePos);
            for (QGraphicsItem* item : items) {
                if (item->type() == QGraphicsEllipseItem::Type) {
                    // 在点的范围内，获取点的数据并显示信息标签
                    name = item->data(Qt::UserRole).toString();
                    QPointF viewPos = mapFromScene(item->sceneBoundingRect().center());
                    showInfoLabel(viewPos, name);
                    foundPoint = true;
                    break; // 找到了点就退出循环
                }
            }
            if (!foundPoint) {
                // 如果没有找到点，则隐藏信息标签
                hideInfoLabel();
            }
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}
// 重写鼠标释放事件
void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton) {
        // 停止拖动
        isDragging = false;
        // 恢复鼠标箭头形状
        unsetCursor();
    }
    QGraphicsView::mouseReleaseEvent(event);
}
// 重写滚轮事件
void CustomGraphicsView::wheelEvent(QWheelEvent *event){
    // 获取滚轮滚动的角度
    qreal angleDelta = event->angleDelta().y();
    // 计算缩放比例
    qreal scaleFactor = qPow(1.2, angleDelta / 120);
    // 获取当前变换矩阵
    QTransform currentTransform = transform();
    // 将变换中心设置为滚轮事件发生的位置
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // 缩放视图
    scale(scaleFactor, scaleFactor);
}
void CustomGraphicsView::showInfoLabel(const QPointF& pos, const QString& text){
    if (!m_infoLabel) {
        m_infoLabel = new QGraphicsTextItem(text);
        m_infoLabel->setFont(QFont("黑体"));
        m_infoLabel->setDefaultTextColor(Qt::black);
        scene()->addItem(m_infoLabel);
    }
    m_infoLabel->setPos(pos.x(),pos.y());
    m_infoLabel->setVisible(true);
}
void CustomGraphicsView::hideInfoLabel(){
    if (m_infoLabel) {
        m_infoLabel->setVisible(false);
        m_infoLabel = nullptr;
    }
}

