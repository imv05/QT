#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "class.h"
#include <unordered_map>
#include <QGraphicsView>

class MainGraphicsView : public QGraphicsView
{
public:
    QVector<QGraphicsItem*> highlightItemList;
    MainGraphicsView(QGraphicsScene& scene, QWidget *parent = nullptr);
    void showHighlight();   //将highlightItemList高亮
    void removeHighlight(); //移除高亮
    QGraphicsItem* mask;    //半透明遮罩的item指针
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    bool highlightActivated;    //是否在高亮模式
    QVector<QGraphicsTextItem*> numberItemList; //用于显示到达各站的时间
    const qreal HIGHLIGHT_ELEVATION = 200;  //高亮对象zpos的抬升值
    const qreal TIME_TEXT_ZVALUE = 40;
    bool isDragging; // 是否正在拖动
    bool timeDisplayed; //到各站的时间是否显示
    QPoint lastMousePos; // 上次鼠标位置
    QGraphicsScene& scene_;
    QGraphicsTextItem* m_infoLabel = nullptr;
    void showInfoLabel(const QPointF& pos, const QString& text);
    void hideInfoLabel();
    void paintTime(QGraphicsScene& sc, std::unordered_map<Station*, int> timeMap);
    void clearTime(QGraphicsScene& sc);
};


#endif // MAINVIEW_H
