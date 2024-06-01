#include "mainview.h"
#include "item.h"
#include "paintmain.h"
#include "search.h"
#include "class.h"

#include <QDebug>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QMessageBox>
#include <QGraphicsItem>

MainGraphicsView::MainGraphicsView(QGraphicsScene& scene, QWidget *parent)
    : QGraphicsView(parent), isDragging(false), scene_(scene){
    highlightActivated = false;
    timeDisplayed = false;
    mask = new TransparentMaskItem(&scene_);    //透明遮罩
    scene_.addItem(mask);
    mask->setZValue(-1*HIGHLIGHT_ELEVATION);
    setMouseTracking(true); // 开启鼠标跟踪
}
// 重写鼠标按下事件
void MainGraphicsView::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton) {
        lastMousePos = event->pos();    // 记录当前鼠标位置
        isDragging = true;      //设置拖拽状态
        setCursor(Qt::ClosedHandCursor);    // 设置鼠标抓手形状
    }else{
        if(timeDisplayed){
            clearTime(scene_); //也会顺带把时间显示的高亮清除掉
        }else if(highlightActivated){//其他高亮（单线、规划）
            removeHighlight();
        }else{
            QPointF scenePos = mapToScene(event->pos());    // 将鼠标事件转换为场景坐标
            for (QGraphicsItem *item : scene_.items(scenePos)) {// 检查每个形状对象是否被点击
                if (item->data(itemType) == StationItem::myType) {//如果是站点
                    QString sname = item->data(itemName).toString();
                    Station* fromstn = allStationNames[sname];
                    Plan::stationA = fromstn;
                    highlightItemList.push_back(Plan::stationA->item);
                    highlightItemList.push_back(Plan::stationA->textItem);
                    Plan::makePlan();
                    paintTime(scene_, Plan::timeMap);
                    // 弹出包含注释内容的消息框
                    // QMessageBox::information(this, "title", sname+"到各站的时间（分钟）");
                    // clearTime(scene_);
                    return;
                }
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}
// 重写鼠标移动事件
void MainGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (isDragging) {
        QPoint delta = event->pos() - lastMousePos; // 计算鼠标移动的距离
        translate(delta.x(), delta.y());    // 平移视图
        lastMousePos = event->pos();    // 更新上次鼠标位置
    }else{
        QPointF scenePos = mapToScene(event->pos());    // 将鼠标位置转换为场景坐标
        // 检查是否在点的范围内
        bool foundPoint = false; // 用于标记是否找到了点
        QString name;
        QList<QGraphicsItem*> items = scene_.items(scenePos);
        for (QGraphicsItem* item : items) {//items是所有范围包含点击时鼠标坐标的对象
            if(item->data(itemType) == StationItem::myType){//如果该对象是车站
                name = item->data(itemName).toString();//获取点的数据并显示信息标签
                showInfoLabel(item->sceneBoundingRect().center(), name);
                foundPoint = true;
                break; // 找到了点就退出循环
            }
        }
        if (!foundPoint) {
            // 如果没有找到点，则隐藏信息标签
            hideInfoLabel();
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}
// 重写鼠标释放事件
void MainGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton) {
        // 停止拖动
        isDragging = false;
        // 恢复鼠标箭头形状
        unsetCursor();
    }
    QGraphicsView::mouseReleaseEvent(event);
}
// 重写滚轮事件
void MainGraphicsView::wheelEvent(QWheelEvent *event){
    // 获取滚轮滚动的角度
    qreal angleDelta = event->angleDelta().y();
    // 计算缩放比例
    qreal scaleFactor = qPow(1.2, angleDelta / 120);
    // 将变换中心设置为滚轮事件发生的位置
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // 缩放视图
    scale(scaleFactor, scaleFactor);
}
void MainGraphicsView::showInfoLabel(const QPointF& pos, const QString& text){
    if (!m_infoLabel) {
        m_infoLabel = new LableItem(pos.x(),pos.y(),text);
        scene()->addItem(m_infoLabel);
    }
    m_infoLabel->setVisible(true);
}
void MainGraphicsView::hideInfoLabel(){
    if (m_infoLabel) {
        m_infoLabel->setVisible(false);
        m_infoLabel = nullptr;
    }
}
void MainGraphicsView::showHighlight(){
    QVector<QGraphicsItem*> temphl;
    if(highlightActivated){//如果有旧信息，先移除
        temphl = highlightItemList;
        removeHighlight();
    }
    highlightItemList = temphl;
    highlightActivated = true;
    for(auto item: highlightItemList){
        if(item!=nullptr){
            if(item->zValue() < HIGHLIGHT_ELEVATION){
                item->setZValue(item->zValue()+HIGHLIGHT_ELEVATION);
                qDebug() << "AAA";
            }
        }
    }
    mask->setZValue(HIGHLIGHT_ELEVATION-1);
}
void MainGraphicsView::removeHighlight(){
    mask->setZValue(-1*HIGHLIGHT_ELEVATION);
    QList<QGraphicsItem*> items = scene_.items();
    for (QGraphicsItem *item : items) {
        if (item->zValue() > HIGHLIGHT_ELEVATION) {
            item->setZValue(item->zValue()-HIGHLIGHT_ELEVATION);
        }
    }
    highlightActivated = false;
    highlightItemList.clear();
}
void MainGraphicsView::paintTime(QGraphicsScene& sc, std::unordered_map<Station*, int> timeMap){
    for(auto sit: allStationNames){
        if(timeMap.find(sit) != timeMap.end() && timeMap[sit]<3600*60*60 && timeMap[sit]>0){
            numberItemList.push_back(sc.addText(QString::number(timeMap[sit]/60)));
            auto nitem = numberItemList.back();
            nitem->setPos(sit->item->pos());
            nitem->setFont(QFont("微软雅黑", 12));
            nitem->setZValue(TIME_TEXT_ZVALUE);
            highlightItemList.push_back(nitem);
        }
    }
    showHighlight();
    timeDisplayed = true;
}
void MainGraphicsView::clearTime(QGraphicsScene& sc){
    for(auto it: numberItemList){
        sc.removeItem(it);
        delete it;
    }
    numberItemList.clear();
    removeHighlight();
    timeDisplayed = false;
}
